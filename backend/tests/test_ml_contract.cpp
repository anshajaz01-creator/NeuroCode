// Checks the T4 <-> T1 contract that fails silently if it drifts.
// Run in CI. Each failure prints what to reconcile.
#include <algorithm>
#include <iostream>
#include <set>
#include "ml/StubPredictor.hpp"
using namespace nc;

int main() {
    int bad = 0;

    // 1. Feature count: IPredictor.hpp says 48, StubPredictor says 53, and the
    //    real extractor must produce exactly the number the model was trained on.
    StubPredictor sp(1);
    const auto feats = sp.extractFeatures("{}", "{}");
    if (kFeatureCount != StubPredictor::kFeatureDim || (int)feats.size() != kFeatureCount) {
        std::cerr << "FAIL feature count: kFeatureCount=" << kFeatureCount
                  << " StubPredictor::kFeatureDim=" << StubPredictor::kFeatureDim
                  << " extractFeatures().size()=" << feats.size()
                  << "  (must all match tools/features.py N_FEATURES)\n";
        ++bad;
    }

    // 2. Labels vs docs/api-spec.md section 9 AlgorithmLabel (T2 mirrors that enum).
    const std::set<std::string> spec = {
        "brute_force_pair_search","binary_search","two_pointer","sliding_window","bfs","dfs",
        "dp_1d","dp_2d","greedy_scan","sort_based","hashing","heap_based","linear_scan",
        "prefix_sum","unknown"};
    for (const auto& l : StubPredictor::labels())
        if (!spec.count(l)) {
            std::cerr << "FAIL label \"" << l << "\" is not in api-spec AlgorithmLabel\n";
            ++bad;
        }

    // 3. Labels must be alphabetical and unique (labels.json order is the class index).
    const auto& L = StubPredictor::labels();
    if (!std::is_sorted(L.begin(), L.end()) || std::set<std::string>(L.begin(), L.end()).size() != L.size()) {
        std::cerr << "FAIL labels not sorted/unique\n"; ++bad;
    }

    if (bad == 0) std::cout << "ml contract OK\n";
    return bad ? 1 : 0;
}