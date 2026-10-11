// Quick smoke test for StubPredictor. No framework needed.
// Build from backend/:
//   g++ -std=c++20 -I src src/ml/StubPredictor.cpp tests/test_predictor_stub.cpp -o test_stub
#include <cassert>
#include <iostream>
#include <memory>

#include "ml/StubPredictor.hpp"

int main()
{
    std::unique_ptr<nc::IPredictor> p = std::make_unique<nc::StubPredictor>(42);

    // features
    auto f = p->extractFeatures("{}", "{}");
    assert(static_cast<int>(f.size()) == nc::StubPredictor::kFeatureDim);

    // model management
    assert(p->loadModel("models/anything.pt"));
    assert(p->activeModelVersion() == "stub-v0");

    // predictions
    int confident = 0;
    for (int run = 0; run < 200; ++run)
    {
        auto g = p->predict(f, 3);
        assert(g.size() == 3);
        float sum = 0;
        for (size_t i = 0; i < g.size(); ++i)
        {
            assert(g[i].probability > 0.0f && g[i].probability <= 1.0f);
            if (i > 0)
                assert(g[i - 1].probability >= g[i].probability); // ranked
            if (i > 0)
                assert(g[i - 1].label != g[i].label); // distinct
            sum += g[i].probability;
        }
        assert(sum <= 1.0001f);
        if (g[0].probability >= 0.5f)
            ++confident;
    }
    // both confident and low-confidence cases must appear
    assert(confident > 20 && confident < 180);

    // k edge cases
    assert(p->predict(f, 0).empty());
    assert(static_cast<int>(p->predict(f, 100).size()) ==
           static_cast<int>(nc::StubPredictor::labels().size()));

    auto g = p->predict(f, 3);
    for (auto &x : g)
        std::cout << x.label << "  " << x.probability << "\n";
    std::cout << "confident runs: " << confident << "/200\n";
    std::cout << "all StubPredictor checks passed\n";
}