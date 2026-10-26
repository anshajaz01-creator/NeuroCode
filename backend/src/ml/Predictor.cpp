#include "ml/Predictor.hpp"

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "ml/StubPredictor.hpp"

namespace nc {

// convert .pt input into .json output
static std::string sidecarPath(const std::string& pt) {
    auto dot = pt.rfind('.');
    return (dot == std::string::npos ? pt : pt.substr(0, dot)) + ".json";
}

//load model
bool Predictor::loadModel(const std::string& checkpoint_path) {
    try {
        std::ifstream in(sidecarPath(checkpoint_path));
        if (!in) return false;
        auto j = nlohmann::json::parse(in);

        // loads four important features needed to be weightesd
        auto labels = j.at("labels").get<std::vector<std::string>>();
        auto mean = j.at("feature_mean").get<std::vector<float>>();
        auto stdev = j.at("feature_std").get<std::vector<float>>();
        int nf = j.at("n_features").get<int>();
        //refuses a model trained on a different feature set
        if (nf != kFeatureCount || (int)mean.size() != nf || (int)stdev.size() != nf) return false;

        //rebuild the network and fill in the weights
        MLP m(nf, static_cast<int64_t>(labels.size()));  // same shape as when saved
        torch::load(m, checkpoint_path);                 // fill in the learned weights
        m->eval();                                       // dropout off permanently

        // swap in only after everything loaded (on failure it keeps the old model working)
        std::lock_guard<std::mutex> lock(mu_);
        model_ = m;
        labels_ = std::move(labels);
        mean_ = std::move(mean);
        std_ = std::move(stdev);
        n_features_ = nf;
        version_ = j.value("version", std::string("unknown"));
        loaded_ = true;
        return true;
    } catch (const std::exception&) {
        return false;
    }
}
// returns model version e.g. "v20261027-1430" thatT3 stores with each analysis
std::string Predictor::activeModelVersion() const {
    std::lock_guard<std::mutex> lock(mu_);
    return version_;
}

std::vector<float> Predictor::extractFeatures(const std::string& ast_json,
                                              const std::string& cfg_json) {
    if (feature_fn_) return feature_fn_(ast_json, cfg_json);
    return std::vector<float>(kFeatureCount, 0.0f);
}

std::vector<AlgorithmGuess> Predictor::predict(const std::vector<float>& features, int k) {
    std::lock_guard<std::mutex> lock(mu_);
    if (!loaded_ || k <= 0) return {};
    if ((int)features.size() != n_features_)
        throw std::invalid_argument("Predictor: expected " + std::to_string(n_features_) +
                                    " features, got " + std::to_string(features.size()));

    // 1. standardize with the TRAINING statistics from the .json (the one we asked from miss shumaila z=x-deviation/mean)
    std::vector<float> z(n_features_);
    for (int f = 0; f < n_features_; ++f) z[f] = (features[f] - mean_[f]) / std_[f];

    // 2. forward pass, no gradients
    torch::NoGradGuard no_grad;
    //from_blob wraps our 53 numbers as a [1, 53] tensor (one sample)
    auto x = torch::from_blob(z.data(), {1, n_features_}, torch::kFloat32);
    //softmax gives probabilities (0,1)
    auto probs = torch::softmax(model_->forward(x), 1).squeeze(0);  // 12 probabilities

    // 3. top k, highest first returns 3 argest prob
    k = std::min<int>(k, (int)labels_.size());
    auto [vals, idxs] = probs.topk(k);
    std::vector<AlgorithmGuess> out;
    for (int i = 0; i < k; ++i)
        out.push_back({labels_[idxs[i].item<int64_t>()], vals[i].item<float>()});
    return out;
}

// ---------- factories declared in IPredictor.hpp ----------

std::unique_ptr<IPredictor> makeStubPredictor() {
    return std::make_unique<StubPredictor>();
}

// Loads the newest .pt in models_dir (file names start with a date, so the
// alphabetically last one is the newest). Falls back to the stub if nothing
// loads, so the server always starts.
std::unique_ptr<IPredictor> makePredictor(const std::string& models_dir) {
    namespace fs = std::filesystem;
    std::vector<std::string> pts;
    if (fs::is_directory(models_dir))
        for (const auto& e : fs::directory_iterator(models_dir))
            if (e.path().extension() == ".pt") pts.push_back(e.path().string());
    std::sort(pts.begin(), pts.end());

    for (auto it = pts.rbegin(); it != pts.rend(); ++it) {
        auto p = std::make_unique<Predictor>();
        if (p->loadModel(*it)) return p;
    }
    std::fprintf(stderr, "makePredictor: no loadable model in %s, using StubPredictor\n",
                 models_dir.c_str());
    return makeStubPredictor();
}

}