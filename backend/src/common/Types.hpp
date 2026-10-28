#pragma once
// Shared enums and the in-memory Job model (T3 owns, all may add).

#include <cctype>
#include <chrono>
#include <cstdint>
#include <ctime>
#include <exception>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "engine/IEngine.hpp"

namespace nc {

enum class JobType { Analyze, Optimize, Train };
enum class JobStatus { Queued, Running, Done, Failed, Cancelled };

inline const char* toString(JobType t) {
    switch (t) {
        case JobType::Analyze:  return "analyze";
        case JobType::Optimize: return "optimize";
        case JobType::Train:    return "train";
    }
    return "analyze";
}

inline const char* toString(JobStatus s) {
    switch (s) {
        case JobStatus::Queued:    return "queued";
        case JobStatus::Running:   return "running";
        case JobStatus::Done:      return "done";
        case JobStatus::Failed:    return "failed";
        case JobStatus::Cancelled: return "cancelled";
    }
    return "queued";
}

inline std::optional<JobType> jobTypeFromString(std::string_view s) {
    if (s == "analyze")  return JobType::Analyze;
    if (s == "optimize") return JobType::Optimize;
    if (s == "train")    return JobType::Train;
    return std::nullopt;
}

inline bool isTerminal(JobStatus s) {
    return s == JobStatus::Done || s == JobStatus::Failed || s == JobStatus::Cancelled;
}

// "2026-10-26T04:57:44Z"
inline std::string nowIso() {
    const std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm{};
    gmtime_r(&t, &tm);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm);
    return buf;
}

// Digits only, at most 18 of them, so it always fits in int64_t.
inline bool parseJobId(const std::string& s, std::int64_t& out) {
    if (s.empty() || s.size() > 18) return false;
    std::int64_t v = 0;
    for (const char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
        v = v * 10 + (c - '0');
    }
    out = v;
    return true;
}

// ---- training ---------------------------------------------------------------
// T3's own types, mirroring TrainRequest / EpochMetrics / TrainResult in api.d.ts.
// They are deliberately NOT named TrainConfig / EpochStats / TrainResult / ModelInfo /
// EpochCallback: ml/Trainer.hpp already defines those names in namespace nc.

struct TrainParams {
    int epochs = 300;
    double learning_rate = 1e-3;
    int batch_size = 32;
    int early_stopping_patience = 25;
};

struct EpochRecord {
    int epoch = 0;
    double train_loss = 0, val_loss = 0, val_accuracy = 0;
};

struct TrainSummary {
    std::string version;
    double accuracy = 0;
    double loss = 0;
    int epochs = 0;
    int dataset_size = 0;
    std::vector<EpochRecord> history;
};

// Thrown from the epoch sink when a training job is cancelled. ml::train() has no cancel
// parameter, so the sink throws and the exception unwinds through train(): T1's training
// code must not catch it.
struct TrainCancelled : std::exception {
    const char* what() const noexcept override { return "training cancelled"; }
};

using EpochSink = std::function<void(const EpochRecord&)>;
// Runs a whole training job on the calling worker thread and returns its summary.
// Real implementation (T1's pipeline) later; services/StubTrainer.cpp until then.
using TrainFn = std::function<TrainSummary(const TrainParams&, const EpochSink&)>;

// One saved model on disk (api.d.ts ModelInfo).
struct ModelEntry {
    std::int64_t id = 0;
    std::string version;
    double accuracy = 0;
    std::optional<double> loss;   // unknown for checkpoints that do not record it
    int epochs = 0;
    int dataset_size = 0;
    std::string trained_at;
    bool is_active = false;
};

// ---- sandbox execute ---------------------------------------------------------

struct ExecuteRequest {
    std::string code;
    std::string stdin_text;
};

struct ExecuteOutcome {          // api.d.ts ExecuteResponse
    bool success = false;
    std::string compile_error;
    std::string stdout_text;
    std::string stderr_text;
    int exit_code = -1;
    double time_ms = 0;
    long memory_kb = 0;
    bool timed_out = false;
};

using ExecuteFn = std::function<ExecuteOutcome(const ExecuteRequest&)>;

using JobResult = std::variant<std::monostate, AnalysisResult, OptimizeResult, TrainSummary>;

struct Job {
    std::int64_t id = 0;
    JobType type = JobType::Analyze;
    JobStatus status = JobStatus::Queued;
    std::string problem_id;      // empty when the problem is custom
    ProblemSpec problem;
    std::string input_code;
    int progress = 0;            // 0..100
    std::string stage;
    std::string error;           // empty when none
    std::string created_at;
    std::string finished_at;     // empty until terminal
    JobResult result;
};

}  // namespace nc
