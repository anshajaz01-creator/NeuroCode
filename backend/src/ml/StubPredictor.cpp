#include "ml/StubPredictor.hpp"

#include <algorithm>
#include <numeric>

namespace nc {

StubPredictor::StubPredictor(unsigned seed) : rng_(seed) {}

const std::vector<std::string>& StubPredictor::labels() {
    static const std::vector<std::string> kLabels = {
        "binary_search",
        "brute_force_pair_search",
        "dp",
        "graph_traversal",
        "greedy_scan",
        "hashing",
        "heap_based",
        "linear_search",
        "naive_recursion",
        "sliding_window",
        "sorting_based",
        "two_pointer",
    };
    return kLabels;
}

std::vector<float> StubPredictor::extractFeatures(const std::string& /*ast_json*/,
                                                  const std::string& /*cfg_json*/) {
    return std::vector<float>(kFeatureDim, 0.0f);
}

std::vector<AlgorithmGuess> StubPredictor::predict(const std::vector<float>& /*features*/,
                                                   int k) {
    const auto& L = labels();
    const int n = static_cast<int>(L.size());
    if (k <= 0) return {};
    k = std::min(k, n);

    // Random score per class, normalised over ALL classes like a real softmax,
    // so the top-k probabilities sum to less than 1.
    std::vector<float> w(n);
    {
        std::lock_guard<std::mutex> lock(mu_);
        std::uniform_real_distribution<float> uni(0.1f, 1.0f);
        for (auto& x : w) x = uni(rng_);

        // Half the time make one class dominant (top prob around 0.65),
        // so the UI sees both confident and "low confidence" (< 0.5) results.
        if (std::bernoulli_distribution(0.5)(rng_)) {
            std::uniform_int_distribution<int> pick(0, n - 1);
            w[pick(rng_)] += 15.0f;
        }
    }
    const float total = std::accumulate(w.begin(), w.end(), 0.0f);

    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::partial_sort(idx.begin(), idx.begin() + k, idx.end(),
                      [&](int a, int b) { return w[a] > w[b]; });

    std::vector<AlgorithmGuess> out;
    out.reserve(k);
    for (int i = 0; i < k; ++i) out.push_back({L[idx[i]], w[idx[i]] / total});
    return out;
}

bool StubPredictor::loadModel(const std::string& /*checkpoint_path*/) {
    return true;
}

std::string StubPredictor::activeModelVersion() const {
    return "stub-v0";
}

}  // namespace nc