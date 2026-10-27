#pragma once
#include <string>
#include <vector>
#include <functional>
#include <optional>
#include <memory>
#include "AnalysisResult.hpp"

namespace nc {

class IPredictor;   // ml/IPredictor.hpp, forward-declared so T3 never needs it

struct ProblemSpec {
    std::string problem_id;      // empty if custom
    std::string input_type;
    std::string output_type;
    std::string operation;
    long long   max_n = 0;
};

struct BenchmarkResult {
    double before_ms = 0, after_ms = 0;
    long   before_kb = 0, after_kb = 0;
    long long n_used = 0;
};

struct SummaryRow { std::string label, before, after; };

struct OptimizationSummary {
    std::string headline;
    std::string explanation;
    std::vector<SummaryRow> comparison;
    std::vector<std::string> changes;
    std::string tradeoff;
    std::string verification;
    double speedup = 0.0;
};

struct OptimizeResult {
    AnalysisResult analysis;
    std::string recommended_algorithm;
    std::string recommended_complexity;
    std::string optimized_code;
    OptimizationSummary summary;
    bool verified = false;
    BenchmarkResult bench;
    bool success = true;
    std::string error;
};

using ProgressFn = std::function<void(int percent, const std::string& stage)>;

class IEngine {
public:
    virtual ~IEngine() = default;
    virtual AnalysisResult analyze(const std::string& code, const ProblemSpec& spec,
                                   ProgressFn on_progress) = 0;
    virtual OptimizeResult optimize(const std::string& code, const ProblemSpec& spec,
                                    ProgressFn on_progress) = 0;
    virtual void cancel() = 0;
};

// One engine per job. The predictor must outlive the engine, and its methods
// must be safe to call from several worker threads at once.
std::unique_ptr<IEngine> makeEngine(IPredictor& predictor);

} // namespace nc