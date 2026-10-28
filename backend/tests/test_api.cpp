// T3 tests: JobManager, JSON shapes, request validation, catalog, auth, ThreadPool.
// No network and no real engine: a FakeEngine stands in, so the suite runs in about a second.
//
//   cmake -B build -DNC_BUILD_TESTS=ON -DCMAKE_PREFIX_PATH=$HOME/libs/libtorch
//   cmake --build build --target test_api -j2 && ./build/test_api

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <memory>
#include <set>
#include <stdexcept>
#include <thread>

#include "common/Json.hpp"
#include "common/Types.hpp"
#include "services/AuthService.hpp"
#include "services/CodeExecutor.hpp"
#include "services/JobManager.hpp"
#include "services/ModelService.hpp"
#include "services/ProblemCatalog.hpp"
#include "services/ProgressBroadcaster.hpp"
#include "services/RateLimiter.hpp"
#include "services/ThreadPool.hpp"

using namespace nc;
using namespace std::chrono_literals;

namespace {

bool waitFor(const std::function<bool()>& pred, std::chrono::milliseconds limit = 3000ms) {
    const auto end = std::chrono::steady_clock::now() + limit;
    while (std::chrono::steady_clock::now() < end) {
        if (pred()) return true;
        std::this_thread::sleep_for(5ms);
    }
    return pred();
}

// Holds engines at their first step until opened, so tests control timing exactly.
struct Gate {
    std::atomic<bool> open{false};
};

enum class Mode { Succeed, Fail, Throw };

class FakeEngine : public IEngine {
public:
    FakeEngine(std::shared_ptr<Gate> gate, Mode mode) : gate_(std::move(gate)), mode_(mode) {}

    AnalysisResult analyze(const std::string&, const ProblemSpec&, ProgressFn on_progress) override {
        return run(on_progress);
    }
    OptimizeResult optimize(const std::string&, const ProblemSpec&, ProgressFn on_progress) override {
        OptimizeResult r;
        r.analysis = run(on_progress);
        r.success = r.analysis.success;
        r.error = r.analysis.error;
        r.verified = r.success;
        return r;
    }
    void cancel() override { cancelled_ = true; }

private:
    AnalysisResult run(const ProgressFn& on_progress) {
        AnalysisResult r;
        while (gate_ && !gate_->open && !cancelled_) std::this_thread::sleep_for(2ms);
        if (cancelled_) { r.success = false; r.error = "cancelled"; return r; }
        if (mode_ == Mode::Throw) throw std::runtime_error("boom");
        if (on_progress) { on_progress(25, "a"); on_progress(60, "b"); }
        if (mode_ == Mode::Fail) { r.success = false; r.error = "compile error: line 3"; return r; }
        r.algorithms = {{"hashing", 0.9f}};
        r.success = true;
        return r;
    }
    std::shared_ptr<Gate> gate_;
    Mode mode_;
    std::atomic<bool> cancelled_{false};
};

ProblemSpec spec() { return {"pair_sum", "int_array", "bool", "pair_sum", 1000}; }

struct Fixture : ::testing::Test {
    std::shared_ptr<Gate> gate = std::make_shared<Gate>();
    Mode mode = Mode::Succeed;
    ProgressBroadcaster bc;

    std::unique_ptr<JobManager> make(std::size_t workers = 2, std::size_t history = 100) {
        return std::make_unique<JobManager>(
            [this] { return std::make_shared<FakeEngine>(gate, mode); }, workers, history, bc);
    }
    static bool reaches(JobManager& m, std::int64_t id, JobStatus s) {
        return waitFor([&] { auto j = m.get(id); return j && j->status == s; });
    }
};

}  // namespace

// ---------------------------------------------------------------- JobManager

TEST_F(Fixture, JobRunsToDoneWithResult) {
    gate->open = true;
    auto m = make();
    const auto id = m->submit(JobType::Analyze, "code", spec());
    ASSERT_TRUE(reaches(*m, id, JobStatus::Done));
    const auto j = *m->get(id);
    EXPECT_EQ(j.progress, 100);
    EXPECT_EQ(j.stage, "complete");
    EXPECT_FALSE(j.finished_at.empty());
    EXPECT_TRUE(j.error.empty());
    ASSERT_TRUE(std::holds_alternative<AnalysisResult>(j.result));
    EXPECT_EQ(std::get<AnalysisResult>(j.result).algorithms[0].label, "hashing");
}

TEST_F(Fixture, OptimizeJobStoresOptimizeResult) {
    gate->open = true;
    auto m = make();
    const auto id = m->submit(JobType::Optimize, "code", spec());
    ASSERT_TRUE(reaches(*m, id, JobStatus::Done));
    EXPECT_TRUE(std::holds_alternative<OptimizeResult>(m->get(id)->result));
}

TEST_F(Fixture, EngineFailureBecomesFailedAndKeepsResult) {
    gate->open = true;
    mode = Mode::Fail;
    auto m = make();
    const auto id = m->submit(JobType::Analyze, "code", spec());
    ASSERT_TRUE(reaches(*m, id, JobStatus::Failed));
    const auto j = *m->get(id);
    EXPECT_EQ(j.error, "compile error: line 3");
    EXPECT_TRUE(std::holds_alternative<AnalysisResult>(j.result));
}

TEST_F(Fixture, EngineExceptionBecomesFailed) {
    gate->open = true;
    mode = Mode::Throw;
    auto m = make();
    const auto id = m->submit(JobType::Analyze, "code", spec());
    ASSERT_TRUE(reaches(*m, id, JobStatus::Failed));
    EXPECT_NE(m->get(id)->error.find("boom"), std::string::npos);
}

TEST_F(Fixture, WorkerLimitIsRespected) {
    auto m = make(/*workers=*/2);
    std::vector<std::int64_t> ids;
    for (int i = 0; i < 4; ++i) ids.push_back(m->submit(JobType::Analyze, "c", spec()));
    ASSERT_TRUE(waitFor([&] {
        int running = 0;
        for (auto id : ids) running += m->get(id)->status == JobStatus::Running;
        return running == 2;
    }));
    std::this_thread::sleep_for(50ms);   // a third must not start
    int running = 0, queued = 0;
    for (auto id : ids) {
        const auto s = m->get(id)->status;
        running += s == JobStatus::Running;
        queued += s == JobStatus::Queued;
    }
    EXPECT_EQ(running, 2);
    EXPECT_EQ(queued, 2);
    gate->open = true;
    for (auto id : ids) EXPECT_TRUE(reaches(*m, id, JobStatus::Done));
}

TEST_F(Fixture, CancelQueuedJobIsImmediateAndStaysCancelled) {
    auto m = make(/*workers=*/1);
    const auto a = m->submit(JobType::Analyze, "c", spec());
    ASSERT_TRUE(waitFor([&] { return m->get(a)->status == JobStatus::Running; }));
    const auto b = m->submit(JobType::Analyze, "c", spec());
    EXPECT_EQ(m->cancel(b), JobManager::CancelResult::Cancelled);
    EXPECT_EQ(m->get(b)->status, JobStatus::Cancelled);
    gate->open = true;
    EXPECT_TRUE(reaches(*m, a, JobStatus::Done));
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(m->get(b)->status, JobStatus::Cancelled);   // the worker skipped it
}

TEST_F(Fixture, CancelRunningJobEndsCancelledAndDoesNotAffectNextJob) {
    auto m = make(/*workers=*/1);
    const auto a = m->submit(JobType::Analyze, "c", spec());
    ASSERT_TRUE(waitFor([&] { return m->get(a)->status == JobStatus::Running; }));
    EXPECT_EQ(m->cancel(a), JobManager::CancelResult::Requested);
    ASSERT_TRUE(reaches(*m, a, JobStatus::Cancelled));
    EXPECT_EQ(m->get(a)->error, "cancelled");

    gate->open = true;
    const auto b = m->submit(JobType::Analyze, "c", spec());   // fresh engine, flag not inherited
    EXPECT_TRUE(reaches(*m, b, JobStatus::Done));
}

TEST_F(Fixture, CancelUnknownAndFinished) {
    gate->open = true;
    auto m = make();
    EXPECT_EQ(m->cancel(12345), JobManager::CancelResult::NotFound);
    const auto id = m->submit(JobType::Analyze, "c", spec());
    ASSERT_TRUE(reaches(*m, id, JobStatus::Done));
    EXPECT_EQ(m->cancel(id), JobManager::CancelResult::AlreadyFinished);
}

TEST_F(Fixture, ListIsNewestFirstWithoutResults) {
    gate->open = true;
    auto m = make();
    std::vector<std::int64_t> ids;
    for (int i = 0; i < 4; ++i) ids.push_back(m->submit(JobType::Analyze, "c", spec()));
    for (auto id : ids) ASSERT_TRUE(reaches(*m, id, JobStatus::Done));
    const auto l = m->list(3);
    ASSERT_EQ(l.size(), 3u);
    EXPECT_EQ(l[0].id, ids[3]);
    EXPECT_EQ(l[2].id, ids[1]);
    for (const auto& j : l) EXPECT_TRUE(std::holds_alternative<std::monostate>(j.result));
}

TEST_F(Fixture, HistoryIsCapped) {
    gate->open = true;
    auto m = make(/*workers=*/2, /*history=*/3);
    std::int64_t last = 0;
    for (int i = 0; i < 8; ++i) {
        last = m->submit(JobType::Analyze, "c", spec());
        ASSERT_TRUE(reaches(*m, last, JobStatus::Done));
    }
    EXPECT_LE(m->list(100).size(), 4u);   // cap applies on submit, so the newest can sit one over
    EXPECT_TRUE(m->get(last).has_value());
    EXPECT_FALSE(m->get(1).has_value());
}

TEST_F(Fixture, ProgressIsRecordedOnTheJob) {
    gate->open = true;
    auto m = make();
    const auto id = m->submit(JobType::Analyze, "c", spec());
    ASSERT_TRUE(reaches(*m, id, JobStatus::Done));
    EXPECT_EQ(m->get(id)->progress, 100);
}

TEST_F(Fixture, DestructorStopsBlockedJobsQuickly) {
    const auto t0 = std::chrono::steady_clock::now();
    {
        auto m = make(/*workers=*/2);
        for (int i = 0; i < 5; ++i) m->submit(JobType::Analyze, "c", spec());
        std::this_thread::sleep_for(30ms);
    }   // gate never opened: shutdown must cancel instead of hanging
    EXPECT_LT(std::chrono::steady_clock::now() - t0, 2s);
}

// ---------------------------------------------------------------- JSON shapes

namespace {
std::set<std::string> keys(const nlohmann::json& j) {
    std::set<std::string> k;
    for (auto it = j.begin(); it != j.end(); ++it) k.insert(it.key());
    return k;
}
}  // namespace

TEST(Json, AnalysisResultMatchesApiDts) {
    AnalysisResult r;
    r.algorithms = {{"hashing", 0.123456f}};
    r.findings = {{14, "low", "overflow_risk", "m"}};
    r.counterexamples = {{"in", "exp", "act"}};
    const nlohmann::json j = r;
    EXPECT_EQ(keys(j), (std::set<std::string>{"algorithms", "complexity", "findings", "counterexamples",
                                              "ast_json", "cfg_json", "optimization_available",
                                              "success", "error"}));
    EXPECT_EQ(keys(j["complexity"]), (std::set<std::string>{"time", "space", "derivation"}));
    EXPECT_EQ(keys(j["findings"][0]), (std::set<std::string>{"line", "severity", "type", "message"}));
    EXPECT_EQ(keys(j["counterexamples"][0]),
              (std::set<std::string>{"input", "expected_output", "actual_output"}));
    EXPECT_DOUBLE_EQ(j["algorithms"][0]["probability"].get<double>(), 0.1235);   // rounded to 4 places
}

TEST(Json, OptimizeResultMatchesApiDts) {
    const nlohmann::json j = OptimizeResult{};
    EXPECT_EQ(keys(j), (std::set<std::string>{"analysis", "recommended_algorithm", "recommended_complexity",
                                              "optimized_code", "summary", "verified", "bench",
                                              "success", "error"}));
    EXPECT_EQ(keys(j["summary"]), (std::set<std::string>{"headline", "explanation", "comparison", "changes",
                                                         "tradeoff", "verification", "speedup"}));
    EXPECT_EQ(keys(j["bench"]), (std::set<std::string>{"before_ms", "after_ms", "before_kb", "after_kb", "n_used"}));
}

TEST(Json, JobUsesNullsForEmptyOptionalFields) {
    Job job;
    job.id = 7;
    job.problem = spec();
    job.problem.problem_id.clear();
    const nlohmann::json j = job;
    EXPECT_EQ(keys(j), (std::set<std::string>{"id", "type", "status", "problem_id", "problem", "input_code",
                                              "progress", "stage", "error", "created_at", "finished_at",
                                              "result"}));
    EXPECT_TRUE(j["problem_id"].is_null());
    EXPECT_TRUE(j["error"].is_null());
    EXPECT_TRUE(j["finished_at"].is_null());
    EXPECT_TRUE(j["result"].is_null());
    EXPECT_EQ(j["status"], "queued");
    EXPECT_EQ(j["type"], "analyze");
}

TEST(Json, InvalidUtf8DoesNotThrowWhenSerialising) {
    const nlohmann::json j = {{"s", std::string("bad \xC3\x28 byte")}};
    EXPECT_NO_THROW(dumpSafe(j));
}

// ---------------------------------------------------------------- validation

TEST(ParseProblemSpec, AcceptsAValidSpec) {
    ProblemSpec p;
    std::string err;
    const auto j = nlohmann::json{{"problem_id", ""}, {"input_type", "int_array"}, {"output_type", "bool"},
                                  {"operation", "pair_sum"}, {"max_n", 100000}};
    ASSERT_TRUE(parseProblemSpec(j, p, err)) << err;
    EXPECT_EQ(p.max_n, 100000);
    EXPECT_TRUE(p.problem_id.empty());
}

TEST(ParseProblemSpec, RejectsBadInput) {
    const nlohmann::json good = {{"input_type", "a"}, {"output_type", "b"}, {"operation", "c"}, {"max_n", 5}};
    auto bad = [&](const std::function<void(nlohmann::json&)>& mutate) {
        nlohmann::json j = good;
        mutate(j);
        ProblemSpec p;
        std::string err;
        const bool ok = parseProblemSpec(j, p, err);
        return !ok && !err.empty();
    };
    EXPECT_TRUE(bad([](auto& j) { j.erase("operation"); }));
    EXPECT_TRUE(bad([](auto& j) { j["operation"] = ""; }));
    EXPECT_TRUE(bad([](auto& j) { j["input_type"] = 5; }));
    EXPECT_TRUE(bad([](auto& j) { j["max_n"] = 0; }));
    EXPECT_TRUE(bad([](auto& j) { j["max_n"] = 2000000000; }));
    EXPECT_TRUE(bad([](auto& j) { j["max_n"] = "5"; }));
    EXPECT_TRUE(bad([](auto& j) { j["max_n"] = 1.5; }));
    EXPECT_TRUE(bad([](auto& j) { j["operation"] = std::string(65, 'x'); }));
    ProblemSpec p;
    std::string err;
    EXPECT_FALSE(parseProblemSpec(nlohmann::json::array(), p, err));
}

TEST(ParseJobId, OnlyDigitsAndBoundedLength) {
    std::int64_t id = 0;
    EXPECT_TRUE(parseJobId("42", id));
    EXPECT_EQ(id, 42);
    EXPECT_FALSE(parseJobId("", id));
    EXPECT_FALSE(parseJobId("-1", id));
    EXPECT_FALSE(parseJobId("4x", id));
    EXPECT_FALSE(parseJobId("1234567890123456789", id));   // 19 digits
}

// ---------------------------------------------------------------- catalog, auth, pool

TEST(ProblemCatalog, HasFiveProblemsAndLookupWorks) {
    ProblemCatalog c;
    EXPECT_EQ(c.all().size(), 5u);
    ASSERT_NE(c.find("pair_sum"), nullptr);
    EXPECT_EQ(c.find("pair_sum")->optimal_time, "O(n)");
    EXPECT_EQ(c.find("nope"), nullptr);
    std::set<std::string> ids;
    for (const auto& p : c.all()) ids.insert(p.id);
    EXPECT_EQ(ids.size(), 5u);   // unique ids
}

TEST(AuthService, LoginValidateLogout) {
    AuthService a("demo", "secret");
    EXPECT_FALSE(a.login("demo", "wrong"));
    EXPECT_FALSE(a.login("other", "secret"));
    const auto t1 = a.login("demo", "secret");
    const auto t2 = a.login("demo", "secret");
    ASSERT_TRUE(t1 && t2);
    EXPECT_EQ(t1->size(), 64u);
    EXPECT_NE(*t1, *t2);
    EXPECT_TRUE(a.validate(*t1));
    EXPECT_FALSE(a.validate(""));
    EXPECT_FALSE(a.validate("nope"));
    a.logout(*t1);
    EXPECT_FALSE(a.validate(*t1));
    EXPECT_TRUE(a.validate(*t2));
}

TEST(ThreadPool, RunsEveryTaskOnWorkerThreads) {
    std::atomic<int> done{0};
    std::set<std::thread::id> threads;
    std::mutex mu;
    {
        ThreadPool pool(3);
        for (int i = 0; i < 30; ++i) {
            pool.submit([&] {
                std::this_thread::sleep_for(1ms);
                { std::lock_guard<std::mutex> lk(mu); threads.insert(std::this_thread::get_id()); }
                ++done;
            });
        }
        EXPECT_TRUE(waitFor([&] { return done == 30; }));
    }
    EXPECT_EQ(done, 30);
    EXPECT_LE(threads.size(), 3u);
    EXPECT_EQ(threads.count(std::this_thread::get_id()), 0u);
}


// ================================================================ training jobs

namespace {
TrainFn quickTrain() {
    return [](const TrainParams&, const EpochSink& sink) {
        TrainSummary s;
        for (int e = 1; e <= 3; ++e) {
            EpochRecord r;
            r.epoch = e;
            r.val_accuracy = 0.5 + 0.1 * e;
            sink(r);
            s.history.push_back(r);
        }
        s.version = "v-test";
        s.epochs = 3;
        s.accuracy = 0.8;
        return s;
    };
}
}  // namespace

TEST_F(Fixture, TrainJobCompletesWithSummary) {
    auto m = make();
    m->setTrainFn(quickTrain());
    const auto id = m->submitTrain(TrainParams{});
    ASSERT_TRUE(id.has_value());
    ASSERT_TRUE(reaches(*m, *id, JobStatus::Done));
    const auto j = *m->get(*id);
    EXPECT_EQ(j.type, JobType::Train);
    EXPECT_EQ(j.progress, 100);
    ASSERT_TRUE(std::holds_alternative<TrainSummary>(j.result));
    EXPECT_EQ(std::get<TrainSummary>(j.result).version, "v-test");
    EXPECT_EQ(std::get<TrainSummary>(j.result).history.size(), 3u);
}

TEST_F(Fixture, OnlyOneTrainingJobAtATime) {
    auto m = make();
    m->setTrainFn([this](const TrainParams&, const EpochSink& sink) {
        int e = 0;
        while (!gate->open) {
            EpochRecord r;
            r.epoch = ++e;
            sink(r);
            std::this_thread::sleep_for(3ms);
        }
        return TrainSummary{};
    });
    const auto a = m->submitTrain(TrainParams{});
    ASSERT_TRUE(a.has_value());
    EXPECT_TRUE(m->trainingActive());
    EXPECT_FALSE(m->submitTrain(TrainParams{}).has_value());   // refused while one is active
    // analyze jobs are not blocked by training
    gate->open = true;
    ASSERT_TRUE(reaches(*m, *a, JobStatus::Done));
    EXPECT_FALSE(m->trainingActive());
    EXPECT_TRUE(m->submitTrain(TrainParams{}).has_value());
}

TEST_F(Fixture, CancellingTrainingUnwindsThroughTheTrainer) {
    auto m = make();
    std::atomic<bool> unwound{false};
    m->setTrainFn([&](const TrainParams&, const EpochSink& sink) {
        struct Guard { std::atomic<bool>& f; ~Guard() { f = true; } } guard{unwound};
        for (int e = 1;; ++e) {
            EpochRecord r;
            r.epoch = e;
            sink(r);   // throws TrainCancelled once cancel() was called
            std::this_thread::sleep_for(3ms);
        }
        return TrainSummary{};
    });
    const auto id = m->submitTrain(TrainParams{});
    ASSERT_TRUE(id.has_value());
    ASSERT_TRUE(waitFor([&] { return m->get(*id)->progress > 0 || m->get(*id)->stage.rfind("epoch", 0) == 0; }));
    EXPECT_EQ(m->cancel(*id), JobManager::CancelResult::Requested);
    ASSERT_TRUE(reaches(*m, *id, JobStatus::Cancelled));
    EXPECT_TRUE(unwound);
    EXPECT_FALSE(m->trainingActive());
}

TEST_F(Fixture, TrainerExceptionBecomesFailed) {
    auto m = make();
    m->setTrainFn([](const TrainParams&, const EpochSink&) -> TrainSummary { throw std::runtime_error("out of memory"); });
    const auto id = m->submitTrain(TrainParams{});
    ASSERT_TRUE(reaches(*m, *id, JobStatus::Failed));
    EXPECT_NE(m->get(*id)->error.find("out of memory"), std::string::npos);
}

TEST_F(Fixture, TrainingWithoutATrainFnFailsCleanly) {
    auto m = make();
    EXPECT_FALSE(m->canTrain());
    const auto id = m->submitTrain(TrainParams{});
    ASSERT_TRUE(reaches(*m, *id, JobStatus::Failed));
}

TEST(ParseTrainParams, DefaultsAndOverrides) {
    TrainParams p;
    std::string err;
    ASSERT_TRUE(parseTrainParams(nlohmann::json::object(), p, err)) << err;
    EXPECT_EQ(p.epochs, 300);
    EXPECT_EQ(p.batch_size, 32);
    EXPECT_EQ(p.early_stopping_patience, 25);
    EXPECT_DOUBLE_EQ(p.learning_rate, 1e-3);

    ASSERT_TRUE(parseTrainParams({{"epochs", 50}, {"learning_rate", 0.01}, {"batch_size", 64},
                                  {"early_stopping_patience", 10}}, p, err)) << err;
    EXPECT_EQ(p.epochs, 50);
    EXPECT_DOUBLE_EQ(p.learning_rate, 0.01);
    EXPECT_EQ(p.batch_size, 64);
    EXPECT_EQ(p.early_stopping_patience, 10);
}

TEST(ParseTrainParams, RejectsBadValues) {
    auto bad = [](const nlohmann::json& j) {
        TrainParams p;
        std::string err;
        return !parseTrainParams(j, p, err) && !err.empty();
    };
    EXPECT_TRUE(bad({{"epochs", 0}}));
    EXPECT_TRUE(bad({{"epochs", 5000}}));
    EXPECT_TRUE(bad({{"epochs", "5"}}));
    EXPECT_TRUE(bad({{"epochs", 2.5}}));
    EXPECT_TRUE(bad({{"learning_rate", 0}}));
    EXPECT_TRUE(bad({{"learning_rate", 2}}));
    EXPECT_TRUE(bad({{"learning_rate", "fast"}}));
    EXPECT_TRUE(bad({{"batch_size", 0}}));
    EXPECT_TRUE(bad({{"early_stopping_patience", 0}}));
    EXPECT_TRUE(bad(nlohmann::json::array()));
}

TEST(Json, TrainModelAndExecuteShapesMatchApiDts) {
    TrainSummary t;
    t.history = {{1, 0.5, 0.6, 0.7}};
    const nlohmann::json tj = t;
    EXPECT_EQ(keys(tj), (std::set<std::string>{"version", "accuracy", "loss", "epochs", "dataset_size", "history"}));
    EXPECT_EQ(keys(tj["history"][0]), (std::set<std::string>{"epoch", "train_loss", "val_loss", "val_accuracy"}));

    ModelEntry m;
    const nlohmann::json mj = m;
    EXPECT_EQ(keys(mj), (std::set<std::string>{"id", "version", "accuracy", "loss", "epochs", "dataset_size",
                                               "trained_at", "is_active"}));
    EXPECT_TRUE(mj["loss"].is_null());
    m.loss = 0.25;
    EXPECT_DOUBLE_EQ(nlohmann::json(m)["loss"].get<double>(), 0.25);

    const nlohmann::json ej = ExecuteOutcome{};
    EXPECT_EQ(keys(ej), (std::set<std::string>{"success", "compile_error", "stdout", "stderr", "exit_code",
                                               "time_ms", "memory_kb", "timed_out"}));

    Job job;
    job.type = JobType::Train;
    job.result = t;
    const nlohmann::json jj = job;
    EXPECT_TRUE(jj["problem"].is_null());
    EXPECT_EQ(jj["type"], "train");
    EXPECT_EQ(keys(jj["result"]), keys(tj));
}

// ================================================================ CodeExecutor

TEST(CodeExecutor, RunsOffTheCallingThreadAndReturnsTheOutcome) {
    CodeExecutor ex([](const ExecuteRequest& r) {
        ExecuteOutcome o;
        o.success = true;
        o.stdout_text = r.code + "|" + r.stdin_text;
        return o;
    }, 1, 4);
    std::promise<ExecuteOutcome> p;
    auto f = p.get_future();
    ASSERT_TRUE(ex.submit({"code", "in"}, [&](ExecuteOutcome o) { p.set_value(std::move(o)); }));
    ASSERT_EQ(f.wait_for(2s), std::future_status::ready);
    const auto o = f.get();
    EXPECT_TRUE(o.success);
    EXPECT_EQ(o.stdout_text, "code|in");
}

TEST(CodeExecutor, RefusesWorkWhenTooManyArePending) {
    auto gate = std::make_shared<Gate>();
    CodeExecutor ex([gate](const ExecuteRequest&) {
        while (!gate->open) std::this_thread::sleep_for(2ms);
        return ExecuteOutcome{};
    }, 1, 2);
    std::atomic<int> done{0};
    auto cb = [&](ExecuteOutcome) { ++done; };
    EXPECT_TRUE(ex.submit({"a", ""}, cb));
    EXPECT_TRUE(ex.submit({"b", ""}, cb));
    EXPECT_FALSE(ex.submit({"c", ""}, cb));   // 2 pending already
    gate->open = true;
    ASSERT_TRUE(waitFor([&] { return done == 2; }));
    EXPECT_TRUE(waitFor([&] { return ex.submit({"d", ""}, cb); }));   // room again
    gate->open = true;
}

TEST(CodeExecutor, ExceptionBecomesAnInternalError) {
    CodeExecutor ex([](const ExecuteRequest&) -> ExecuteOutcome { throw std::runtime_error("x"); }, 1, 2);
    std::promise<ExecuteOutcome> p;
    auto f = p.get_future();
    ASSERT_TRUE(ex.submit({"c", ""}, [&](ExecuteOutcome o) { p.set_value(std::move(o)); }));
    ASSERT_EQ(f.wait_for(2s), std::future_status::ready);
    const auto o = f.get();
    EXPECT_FALSE(o.success);
    EXPECT_EQ(o.compile_error, "internal sandbox error");
}

TEST(CodeExecutor, StubReportsThatNothingWasRun) {
    const auto o = makeStubExecuteFn()({"int main(){}", ""});
    EXPECT_FALSE(o.success);
    EXPECT_NE(o.compile_error.find("not connected"), std::string::npos);
}

// ================================================================ ModelService

namespace {
namespace fs = std::filesystem;

struct ModelDir {
    fs::path dir;
    ModelDir() {
        dir = fs::temp_directory_path() / ("nc_models_" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        fs::create_directories(dir);
    }
    ~ModelDir() { std::error_code ec; fs::remove_all(dir, ec); }

    void add(const std::string& stem, const nlohmann::json& meta, bool withPt = true, int ageSeconds = 0) {
        std::ofstream(dir / (stem + ".json")) << meta.dump();
        if (withPt) {
            std::ofstream(dir / (stem + ".pt")) << "weights";
            fs::last_write_time(dir / (stem + ".pt"), fs::file_time_type::clock::now() - std::chrono::seconds(ageSeconds));
        }
    }
    std::string str() const { return dir.string(); }
};
}  // namespace

TEST(ModelService, ListsCompletePairsOldestFirstAndReadsMetadata) {
    ModelDir d;
    d.add("v1", {{"version", "v1"}, {"val_accuracy", 0.8}, {"test_accuracy", 0.84}, {"best_epoch", 40}, {"dataset_size", 2067}}, true, 100);
    d.add("v2", {{"version", "v2"}, {"val_accuracy", 0.9}, {"epochs_run", 55}, {"best_val_loss", 0.31}, {"dataset_size", 2067}}, true, 10);
    d.add("v3", {{"version", "v3"}}, /*withPt=*/false);                 // no weights: skipped
    std::ofstream(d.dir / "bad.json") << "{not json";                    // unreadable: skipped
    std::ofstream(d.dir / "bad.pt") << "x";

    ModelService svc(d.str(), nullptr);
    const auto l = svc.list();
    ASSERT_EQ(l.size(), 2u);
    EXPECT_EQ(l[0].version, "v1");
    EXPECT_DOUBLE_EQ(l[0].accuracy, 0.84);          // test accuracy preferred
    EXPECT_EQ(l[0].epochs, 40);                     // falls back to best_epoch
    EXPECT_FALSE(l[0].loss.has_value());
    EXPECT_EQ(l[1].version, "v2");
    EXPECT_DOUBLE_EQ(l[1].accuracy, 0.9);           // no test accuracy: validation
    EXPECT_EQ(l[1].epochs, 55);
    EXPECT_DOUBLE_EQ(*l[1].loss, 0.31);
    EXPECT_NE(l[0].id, l[1].id);
    EXPECT_EQ(l[0].id, svc.list()[0].id);           // ids are stable between calls
    EXPECT_EQ(l[0].trained_at.size(), 20u);         // 2026-10-26T04:57:44Z
    EXPECT_FALSE(l[0].is_active);
}

TEST(ModelService, MissingDirectoryListsNothing) {
    ModelService svc("/nonexistent/dir/for/test", nullptr);
    EXPECT_TRUE(svc.list().empty());
}

TEST(ModelService, ActivateLoadsTheWeightsAndRemembersTheChoice) {
    ModelDir d;
    d.add("v1", {{"version", "v1"}}, true, 100);
    d.add("v2", {{"version", "v2"}}, true, 10);
    std::string loaded;
    ModelService svc(d.str(), [&](const std::string& pt) { loaded = pt; return true; });

    const auto id2 = svc.list()[1].id;
    const auto r = svc.activate(id2);
    ASSERT_EQ(r.status, ModelService::ActivateStatus::Ok);
    EXPECT_TRUE(r.model->is_active);
    EXPECT_EQ(fs::path(loaded).filename(), "v2.pt");
    const auto l = svc.list();
    EXPECT_FALSE(l[0].is_active);
    EXPECT_TRUE(l[1].is_active);

    // a fresh service (a server restart) restores it
    std::string reloaded;
    ModelService again(d.str(), [&](const std::string& pt) { reloaded = pt; return true; });
    EXPECT_TRUE(again.restoreActive());
    EXPECT_EQ(fs::path(reloaded).filename(), "v2.pt");
}

TEST(ModelService, ActivateErrors) {
    ModelDir d;
    d.add("v1", {{"version", "v1"}}, true, 10);

    ModelService noLoader(d.str(), nullptr);
    EXPECT_EQ(noLoader.activate(noLoader.list()[0].id).status, ModelService::ActivateStatus::NotAvailable);
    EXPECT_EQ(noLoader.activate(999).status, ModelService::ActivateStatus::NotFound);
    EXPECT_FALSE(noLoader.canActivate());

    ModelService failing(d.str(), [](const std::string&) { return false; });
    EXPECT_EQ(failing.activate(failing.list()[0].id).status, ModelService::ActivateStatus::LoadFailed);
    EXPECT_FALSE(failing.list()[0].is_active);                 // a failed load changes nothing
    EXPECT_FALSE(fs::exists(d.dir / "ACTIVE"));
}

// ================================================================ RateLimiter

TEST(RateLimiter, AllowsTheLimitThenBlocksUntilTheWindowResets) {
    RateLimiter rl(3, 60);
    EXPECT_EQ(rl.check("1.2.3.4", 1000), 0);
    EXPECT_EQ(rl.check("1.2.3.4", 1001), 0);
    EXPECT_EQ(rl.check("1.2.3.4", 1002), 0);
    const int wait = rl.check("1.2.3.4", 1003);
    EXPECT_GT(wait, 0);
    EXPECT_LE(wait, 60);
    EXPECT_EQ(rl.check("5.6.7.8", 1003), 0);          // other clients unaffected
    EXPECT_EQ(rl.check("1.2.3.4", 1060), 0);          // new window
}

TEST(RateLimiter, ZeroLimitDisablesIt) {
    RateLimiter rl(0, 60);
    for (int i = 0; i < 1000; ++i) ASSERT_EQ(rl.check("x", 5), 0);
}
