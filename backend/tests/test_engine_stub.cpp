#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>
//#include <nlohmann/json.hpp>
#include "engine/EngineStub.hpp"
#include "ml/StubPredictor.hpp"
#include "FakePredictor.hpp"
using namespace nc;
using namespace std::chrono_literals;

static std::unique_ptr<IEngine> mk(IPredictor& p) { return std::make_unique<EngineStub>(p, 80ms); }

int main() {
    ProblemSpec spec;
    StubPredictor real(42);          // T1's stub, fixed seed
    FakePredictor fake;              // records inputs and injects failures
    std::vector<int> pcts;
    auto cb = [&](int pc, const std::string&) { pcts.push_back(pc); };

    { // happy path with T1's real StubPredictor
        auto r = mk(real)->analyze("code", spec, cb);
        assert(r.success && r.optimization_available);
        assert(r.algorithms.size() == 3);
        const auto& L = StubPredictor::labels();
        for (size_t i = 0; i < r.algorithms.size(); ++i) {
            assert(std::find(L.begin(), L.end(), r.algorithms[i].label) != L.end());
            if (i) assert(r.algorithms[i].probability <= r.algorithms[i-1].probability);
        }
        assert(pcts.front() == 10 && pcts.back() == 100);
        for (size_t i = 1; i < pcts.size(); ++i) assert(pcts[i] > pcts[i-1]);
    }
    { // predictor receives exactly the schema fixtures
        auto r = mk(fake)->analyze("code", spec, nullptr);
        assert(fake.lastAst == r.ast_json && fake.lastCfg == r.cfg_json);
        auto ast = nlohmann::json::parse(r.ast_json);
        auto cfg = nlohmann::json::parse(r.cfg_json);
        assert(ast["schema_version"] == 1 && cfg["schema_version"] == 1);
        assert(!ast["root"]["children"][0].contains("cyclomatic"));   // CFG is the only source
        const auto& f = cfg["functions"][0];
        assert(f["blocks"].size() == 11 && f["edges"].size() == 13);
        assert(static_cast<int>(f["edges"].size()) - static_cast<int>(f["blocks"].size()) + 2 == 4);
        assert(r.algorithms[0].label == "brute_force_pair_search");
    }
    { // optimize happy
        auto r = mk(real)->optimize("code", spec, nullptr);
        assert(r.success && r.verified && !r.optimized_code.empty());
        assert(r.summary.speedup > 0 && !r.summary.tradeoff.empty() && r.summary.comparison.size() == 5);
    }
    { // unverified: no code, no summary
        auto r = mk(real)->optimize("// STUB:unverified", spec, nullptr);
        assert(r.success && !r.verified && r.optimized_code.empty());
        assert(r.summary.headline.empty() && r.summary.changes.empty() && r.summary.speedup == 0.0);
    }
    { // nospeedup
        auto r = mk(real)->optimize("// STUB:nospeedup", spec, nullptr);
        assert(r.verified && r.summary.speedup == 0.0 && r.summary.tradeoff.empty() && !r.summary.headline.empty());
    }
    { // failure codes
        auto a = mk(real)->analyze("// STUB:compile_error", spec, nullptr);
        assert(!a.success && a.error.rfind("COMPILE_ERROR:", 0) == 0);
        auto b = mk(real)->optimize("// STUB:timeout", spec, nullptr);
        assert(!b.success && b.error.rfind("TIMEOUT:", 0) == 0);
    }
    { // predictor failures
        FakePredictor e; e.empty = true;
        assert(mk(e)->analyze("c", spec, nullptr).error.rfind("MODEL_UNAVAILABLE:", 0) == 0);
        FakePredictor t; t.throws = true;
        assert(mk(t)->analyze("c", spec, nullptr).error.rfind("INTERNAL:", 0) == 0);
    }
    { // cancel mid-run
        auto e = std::make_unique<EngineStub>(real, 800ms);
        AnalysisResult r;
        std::thread th([&] { r = e->analyze("c", spec, nullptr); });
        std::this_thread::sleep_for(150ms); e->cancel(); th.join();
        assert(!r.success && r.error == "cancelled");
    }
    { // concurrent jobs sharing one predictor (T3 runs a pool)
        std::vector<std::thread> ts;
        std::atomic<int> ok{0};
        for (int i = 0; i < 8; ++i)
            ts.emplace_back([&] { if (mk(real)->analyze("c", spec, nullptr).success) ++ok; });
        for (auto& t : ts) t.join();
        assert(ok == 8);
    }
    { // factory
        assert(makeEngine(real) != nullptr);
    }
    std::cout << "all engine stub tests passed\n";
}
