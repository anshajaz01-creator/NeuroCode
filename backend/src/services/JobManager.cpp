#include "services/JobManager.hpp"

#include <algorithm>
#include <exception>

#include "common/Logger.hpp"

namespace nc {

JobManager::JobManager(EngineFactory factory, std::size_t workers, std::size_t maxHistory,
                       ProgressBroadcaster& broadcaster)
    : factory_(std::move(factory)),
      bc_(broadcaster),
      maxHistory_(maxHistory),
      pool_(workers) {}

JobManager::~JobManager() {
    // Ask running work to stop so shutdown does not wait for a full analysis or training run.
    std::lock_guard<std::mutex> lk(mu_);
    for (auto& [id, rec] : jobs_) {
        if (isTerminal(rec.job.status)) continue;
        rec.cancel->store(true);
        if (rec.engine) rec.engine->cancel();
        if (rec.job.status == JobStatus::Queued) rec.job.status = JobStatus::Cancelled;
    }
}

std::int64_t JobManager::submit(JobType type, std::string code, ProblemSpec spec) {
    std::shared_ptr<IEngine> engine = factory_();

    std::int64_t id = 0;
    {
        std::lock_guard<std::mutex> lk(mu_);
        id = nextId_++;
        Record rec;
        rec.job.id = id;
        rec.job.type = type;
        rec.job.status = JobStatus::Queued;
        rec.job.problem_id = spec.problem_id;
        rec.job.problem = std::move(spec);
        rec.job.input_code = std::move(code);
        rec.job.created_at = nowIso();
        rec.engine = std::move(engine);
        jobs_.emplace(id, std::move(rec));
        evictLocked();
    }
    pool_.submit([this, id] { run(id); });
    return id;
}

std::optional<std::int64_t> JobManager::submitTrain(TrainParams params) {
    std::int64_t id = 0;
    {
        std::lock_guard<std::mutex> lk(mu_);
        const bool busy = std::any_of(jobs_.begin(), jobs_.end(), [](const auto& kv) {
            return kv.second.job.type == JobType::Train && !isTerminal(kv.second.job.status);
        });
        if (busy) return std::nullopt;
        id = nextId_++;
        Record rec;
        rec.job.id = id;
        rec.job.type = JobType::Train;
        rec.job.status = JobStatus::Queued;
        rec.job.created_at = nowIso();
        rec.train = params;
        jobs_.emplace(id, std::move(rec));
        evictLocked();
    }
    pool_.submit([this, id] { run(id); });
    return id;
}

bool JobManager::trainingActive() const {
    std::lock_guard<std::mutex> lk(mu_);
    return std::any_of(jobs_.begin(), jobs_.end(), [](const auto& kv) {
        return kv.second.job.type == JobType::Train && !isTerminal(kv.second.job.status);
    });
}

std::optional<Job> JobManager::get(std::int64_t id) const {
    std::lock_guard<std::mutex> lk(mu_);
    auto it = jobs_.find(id);
    if (it == jobs_.end()) return std::nullopt;
    return it->second.job;
}

std::vector<Job> JobManager::list(std::size_t limit) const {
    std::vector<Job> out;
    std::lock_guard<std::mutex> lk(mu_);
    for (auto it = jobs_.rbegin(); it != jobs_.rend() && out.size() < limit; ++it) {
        Job copy = it->second.job;
        copy.result = std::monostate{};   // history rows stay small; fetch one job for its result
        out.push_back(std::move(copy));
    }
    return out;
}

JobManager::CancelResult JobManager::cancel(std::int64_t id) {
    bool wasQueued = false;
    {
        std::lock_guard<std::mutex> lk(mu_);
        auto it = jobs_.find(id);
        if (it == jobs_.end()) return CancelResult::NotFound;
        Job& job = it->second.job;
        if (isTerminal(job.status)) return CancelResult::AlreadyFinished;

        it->second.cancel->store(true);
        if (it->second.engine) it->second.engine->cancel();
        if (job.status == JobStatus::Queued) {
            job.status = JobStatus::Cancelled;
            job.error = "cancelled";
            job.stage = "cancelled";
            job.finished_at = nowIso();
            wasQueued = true;
        }
    }
    if (wasQueued) {
        bc_.publishError(id, "cancelled");
        return CancelResult::Cancelled;
    }
    return CancelResult::Requested;
}

void JobManager::run(std::int64_t id) {
    std::shared_ptr<IEngine> engine;
    std::shared_ptr<std::atomic<bool>> cancelFlag;
    JobType type = JobType::Analyze;
    std::string code;
    ProblemSpec spec;
    TrainParams train;
    {
        std::lock_guard<std::mutex> lk(mu_);
        auto it = jobs_.find(id);
        // Not Queued any more means it was cancelled before a worker picked it up.
        if (it == jobs_.end() || it->second.job.status != JobStatus::Queued) return;
        Job& job = it->second.job;
        job.status = JobStatus::Running;
        job.stage = "starting";
        engine = it->second.engine;
        cancelFlag = it->second.cancel;
        type = job.type;
        code = job.input_code;
        spec = job.problem;
        train = it->second.train;
    }
    bc_.publishProgress(id, 0, "starting");

    if (type == JobType::Train) return runTrain(id, train, std::move(cancelFlag));

    ProgressFn onProgress = [this, id](int percent, const std::string& stage) {
        {
            std::lock_guard<std::mutex> lk(mu_);
            auto it = jobs_.find(id);
            if (it != jobs_.end()) {
                it->second.job.progress = percent;
                it->second.job.stage = stage;
            }
        }
        bc_.publishProgress(id, percent, stage);
    };

    try {
        if (type == JobType::Optimize) {
            OptimizeResult r = engine->optimize(code, spec, onProgress);
            const bool ok = r.success;
            const std::string err = r.error;
            complete(id, ok, err, JobResult{std::move(r)});
        } else {
            AnalysisResult r = engine->analyze(code, spec, onProgress);
            const bool ok = r.success;
            const std::string err = r.error;
            complete(id, ok, err, JobResult{std::move(r)});
        }
    } catch (const std::exception& e) {
        NC_LOG_ERROR << "job " << id << " threw: " << e.what();
        complete(id, false, std::string("internal engine error: ") + e.what(), JobResult{});
    } catch (...) {
        NC_LOG_ERROR << "job " << id << " threw an unknown exception";
        complete(id, false, "internal engine error", JobResult{});
    }
}

void JobManager::runTrain(std::int64_t id, const TrainParams& params,
                          std::shared_ptr<std::atomic<bool>> cancel) {
    if (!trainFn_) {
        complete(id, false, "training is not available on this server", JobResult{});
        return;
    }

    const int maxEpochs = std::max(1, params.epochs);
    EpochSink onEpoch = [this, id, cancel, maxEpochs](const EpochRecord& e) {
        if (cancel->load()) throw TrainCancelled{};   // unwinds through the trainer
        const int percent = std::min(99, e.epoch * 100 / maxEpochs);   // 100 is set on completion
        const std::string stage = "epoch " + std::to_string(e.epoch);
        {
            std::lock_guard<std::mutex> lk(mu_);
            auto it = jobs_.find(id);
            if (it != jobs_.end()) {
                it->second.job.progress = percent;
                it->second.job.stage = stage;
            }
        }
        bc_.publishEpoch(id, e.epoch, e.train_loss, e.val_loss, e.val_accuracy);
        bc_.publishProgress(id, percent, stage);
    };

    try {
        TrainSummary s = trainFn_(params, onEpoch);
        complete(id, true, "", JobResult{std::move(s)});
    } catch (const TrainCancelled&) {
        complete(id, false, "cancelled", JobResult{});
    } catch (const std::exception& e) {
        NC_LOG_ERROR << "training job " << id << " threw: " << e.what();
        complete(id, false, std::string("training failed: ") + e.what(), JobResult{});
    } catch (...) {
        NC_LOG_ERROR << "training job " << id << " threw an unknown exception";
        complete(id, false, "training failed", JobResult{});
    }
}

// Succeeded                 -> done
// Error is "cancelled"      -> cancelled
// Anything else             -> failed (any result is kept so the UI can show the message)
void JobManager::complete(std::int64_t id, bool success, const std::string& error, JobResult result) {
    JobStatus status = JobStatus::Done;
    std::string message;
    {
        std::lock_guard<std::mutex> lk(mu_);
        auto it = jobs_.find(id);
        if (it == jobs_.end()) return;
        Job& job = it->second.job;
        job.result = std::move(result);
        job.finished_at = nowIso();
        if (success) {
            status = JobStatus::Done;
            job.progress = 100;
            job.stage = "complete";
        } else if (error == "cancelled") {
            status = JobStatus::Cancelled;
            job.error = "cancelled";
            job.stage = "cancelled";
        } else {
            status = JobStatus::Failed;
            job.error = error.empty() ? "analysis failed" : error;
            job.stage = "failed";
        }
        job.status = status;
        message = job.error;
    }
    if (status == JobStatus::Done) bc_.publishDone(id);
    else bc_.publishError(id, message);
}

// Keeps memory bounded: drops the oldest finished jobs once there are too many.
void JobManager::evictLocked() {
    for (auto it = jobs_.begin(); jobs_.size() > maxHistory_ && it != jobs_.end();) {
        if (isTerminal(it->second.job.status)) it = jobs_.erase(it);
        else ++it;
    }
}

}  // namespace nc
