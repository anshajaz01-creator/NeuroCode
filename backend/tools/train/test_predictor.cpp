#include <cmath>
#include <cstdio>
#include <fstream>
#include <memory>

#include <nlohmann/json.hpp>

#include "ml/Dataset.hpp"
#include "ml/Predictor.hpp"

int main() {
    nc::Dataset ds("data/dataset.jsonl", "src/ml/labels.json");

    // used exactly like the engine will: through the interface
    std::unique_ptr<nc::IPredictor> p = std::make_unique<nc::Predictor>();

    std::printf("load missing file: %s\n", p->loadModel("models/nope.pt") ? "loaded?!" : "false (good)");
    if (!p->loadModel("models/test-save.pt")) { std::printf("load FAILED\n"); return 1; }
    std::printf("loaded version: %s\n\n", p->activeModelVersion().c_str());

    // 1. top-3 for the first 3 test rows, from RAW features
    auto test = ds.indicesOf("test");
    for (int i = 0; i < 3; ++i) {
        const auto& r = ds.rows()[test[i]];
        std::printf("true: %-24s ->", ds.labels()[r.label].c_str());
        for (const auto& g : p->predict(r.features, 3))
            std::printf("  %s %.2f", g.label.c_str(), g.probability);
        std::printf("\n");
    }

    // 2. accuracy through the reloaded Predictor must equal what training measured
    int correct = 0;
    for (size_t i : test) {
        const auto& r = ds.rows()[i];
        if (p->predict(r.features, 1)[0].label == ds.labels()[r.label]) ++correct;
    }
    std::ifstream in("models/test-save.json");
    double saved = nlohmann::json::parse(in)["metrics"]["test_accuracy"];
    double now = (double)correct / test.size();
    std::printf("\ntest accuracy via Predictor: %.4f   saved at training: %.4f   %s\n",
                now, saved, std::abs(now - saved) < 1e-9 ? "MATCH" : "MISMATCH");

    // 3. wrong length rejected
    try {
        p->predict(std::vector<float>(52, 0.f), 3);
        std::printf("52 features: accepted?! (bad)\n");
    } catch (const std::invalid_argument& e) {
        std::printf("52 features: rejected (good)\n");
    }

    // 4. factory picks the newest model in models/
    auto f = nc::makePredictor("models");
    std::printf("makePredictor(\"models\") -> version %s\n", f->activeModelVersion().c_str());
}