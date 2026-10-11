#pragma once
#include <mutex>
#include <random>
#include <string>
#include <vector>

#include "ml/IPredictor.hpp"

namespace nc
{

    // Week 1 stand-in for the real LibTorch predictor.
    // Returns random but well-formed results so T4 can wire inference into the
    // engine and T2 can build the AlgorithmCard before the real model exists.
    // Does NOT depend on LibTorch, so anyone can build it.
    class StubPredictor : public IPredictor
    {
    public:
        // Must match the real FeatureExtractor's output size once it exists.
        static constexpr int kFeatureDim = 50;

        // Pass a fixed seed in tests for repeatable output.
        explicit StubPredictor(unsigned seed = std::random_device{}());

        std::vector<float> extractFeatures(const std::string &ast_json,
                                           const std::string &cfg_json) override;

        std::vector<AlgorithmGuess> predict(const std::vector<float> &features,
                                            int k = 3) override;

        bool loadModel(const std::string &checkpoint_path) override;
        std::string activeModelVersion() const override;

        // The class list. The real model must use the same labels, in the same order.
        static const std::vector<std::string> &labels();

    private:
        std::mt19937 rng_;
        std::mutex mu_; // the engine runs on a thread pool; mt19937 is not thread-safe
    };

} // namespace nc