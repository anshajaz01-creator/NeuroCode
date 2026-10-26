#pragma once
#include <functional>
#include <mutex>
#include <string>
#include <vector>

#include "ml/IPredictor.hpp"
#include "ml/Model.hpp"

namespace nc {


class Predictor : public IPredictor {
public:
    using FeatureFn = std::function<std::vector<float>(const std::string& ast_json,
                                                       const std::string& cfg_json)>;

    std::vector<float> extractFeatures(const std::string& ast_json,
                                       const std::string& cfg_json) override;
    std::vector<AlgorithmGuess> predict(const std::vector<float>& features, int k = 3) override;
    bool loadModel(const std::string& checkpoint_path) override;
    std::string activeModelVersion() const override;

    // T4 C++ FeatureExtractor goes in here. Tb tk extractFeatures returns zeros.
    void setFeatureExtractor(FeatureFn fn) { feature_fn_ = std::move(fn); }

private:
    MLP model_{nullptr};
    std::vector<std::string> labels_;
    std::vector<float> mean_, std_;
    std::string version_ = "none";
    int n_features_ = 0;
    bool loaded_ = false;
    FeatureFn feature_fn_;
    mutable std::mutex mu_;
};

} 