#pragma once
// Queues jobs, runs them on the thread pool, tracks status, supports cancel.
// Jobs live in memory only (no database): they are lost when the server restarts.
// Handles analyze, optimize (through IEngine) and train (through a TrainFn).

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "common/Types.hpp"
#include "engine/IEngine.hpp"
#include "services/ProgressBroadcaster.hpp"
#include "services/ThreadPool.hpp"

namespace nc {

class JobManager {
public:
    // One engine per job. Engine::cancel() sets a flag that is never reset, so a shared
    // engine would cancel every later job as well.
    using EngineFactory = std::function<std::shared_ptr<IEngine>()>;

    enum class CancelResult { Cancelled, Requested, AlreadyFinished, NotFound };

    JobManager(EngineFactory factory, std::size_t workers, std::size_t maxHistory,
               ProgressBroadcaster& broadcaster);
    ~JobManager();

    JobManager(const JobManager&) = delete;
    JobManager& operator=(const JobManager&) = delete;

    // Call before the server starts accepting requests; not synchronised afterwards.
    void setTrainFn(TrainFn fn) { trainFn_ = std::move(fn); }
    bool canTrain() const { return static_cast<bool>(trainFn_); }

    std::int64_t submit(JobType type, std::string code, ProblemSpec spec);   // analyze / optimize
    // nullopt when a training job is already queued or running (one at a time).
    std::optional<std::int64_t> submitTrain(TrainParams params);
    bool trainingActive() const;

    std::optional<Job> get(std::int64_t id) const;
    std::vector<Job> list(std::size_t limit) const;   // newest first, results omitted
    // Queued job: cancelled immediately. Running job: asked to stop, status changes to
    // "cancelled" when it returns.
    CancelResult cancel(std::int64_t id);

private:
    struct Record {
        Job job;
        std::shared_ptr<IEngine> engine;                                    // analyze / optimize
        TrainParams train;                                                  // train
        std::shared_ptr<std::atomic<bool>> cancel = std::make_shared<std::atomic<bool>>(false);
    };

    void run(std::int64_t id);
    void runTrain(std::int64_t id, const TrainParams& params, std::shared_ptr<std::atomic<bool>> cancel);
    void complete(std::int64_t id, bool success, const std::string& error, JobResult result);
    void evictLocked();

    EngineFactory factory_;
    TrainFn trainFn_;
    ProgressBroadcaster& bc_;
    mutable std::mutex mu_;
    std::map<std::int64_t, Record> jobs_;
    std::int64_t nextId_ = 1;
    std::size_t maxHistory_;
    ThreadPool pool_;   // declared last: destroyed first, so workers stop before the rest goes
};

}  // namespace nc
