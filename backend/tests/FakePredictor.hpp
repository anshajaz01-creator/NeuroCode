#pragma once
#include <stdexcept>
#include "ml/IPredictor.hpp"
namespace nc {
class FakePredictor final : public IPredictor {
public:
    std::string lastAst, lastCfg;
    bool empty = false, throws = false;
    std::vector<float> extractFeatures(const std::string& a, const std::string& c) override {
        if (throws) throw std::runtime_error("boom");
        lastAst = a; lastCfg = c; return std::vector<float>(60, 0.f);
    }
    std::vector<AlgorithmGuess> predict(const std::vector<float>&, int) override {
        if (empty) return {};
        return {{"brute_force_pair_search", 0.94f}, {"two_pointer", 0.04f}, {"sliding_window", 0.02f}};
    }
    bool loadModel(const std::string&) override { return true; }
    std::string activeModelVersion() const override { return "fake-v0"; }
};
}