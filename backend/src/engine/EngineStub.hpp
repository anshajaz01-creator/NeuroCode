#pragma once
#include <atomic>
#include <chrono>
#include "IEngine.hpp"

namespace nc {

// Week-1 stub. Returns a fixed, valid result after fake progress steps so T3
// can build the API and T2 the UI without waiting on libclang or LibTorch.
// Algorithm labels come from the real IPredictor (T1's stub or model), and
// ast_json / cfg_json are the real v1 schema fixtures (docs/ast-cfg-schema.md),
// so T1's FeatureExtractor sees production-shaped input from day one.
// Replaced by the real Engine in week 2; makeEngine() keeps its signature.
//
// Lifetime: create ONE engine per job. cancel() sets a flag that is never
// reset, so a cancelled instance must not be reused.
//
// Test hooks (stub only): put one of these comments in the submitted code.
//   // STUB:compile_error  -> failure, "COMPILE_ERROR: ..."
//   // STUB:timeout        -> failure, "TIMEOUT: ..."
//   // STUB:unverified     -> optimize: verified=false, no code, empty summary
//   // STUB:nospeedup      -> optimize: speedup=0 and empty tradeoff
class EngineStub final : public IEngine {
public:
    explicit EngineStub(IPredictor& predictor,
                        std::chrono::milliseconds total_delay = std::chrono::milliseconds(3000))
        : predictor_(predictor), total_delay_(total_delay) {}

    AnalysisResult analyze(const std::string& code, const ProblemSpec& spec,
                           ProgressFn on_progress) override;
    OptimizeResult optimize(const std::string& code, const ProblemSpec& spec,
                            ProgressFn on_progress) override;
    void cancel() override;

private:
    IPredictor& predictor_;
    std::chrono::milliseconds total_delay_;
    std::atomic<bool> cancelled_{false};

    AnalysisResult fakeAnalysis(const std::string& code, const ProblemSpec& spec,
                                ProgressFn on_progress);
};

} // namespace nc