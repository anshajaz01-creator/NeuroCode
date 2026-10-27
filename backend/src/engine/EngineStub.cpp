#include "EngineStub.hpp"

#include <exception>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "ml/IPredictor.hpp"

namespace nc {

namespace {

// Real v1 schema output for tests/fixtures/pair_sum_brute.cpp.
// Generated from the fixture files; see docs/ast-cfg-schema.md.
const char* const kSampleAstJson = R"json({"schema_version":1,"meta":{"source_file":"pair_sum_brute.cpp","language":"cpp","std":"c++20","line_base":"user_code","main_file_only":true},"root":{"type":"program","children":[{"type":"function","name":"hasPair","line":1,"end_line":9,"return_type":"bool","params":[{"type":"vector<int>&","name":"a"},{"type":"int","name":"k"}],"recursive":false,"exprs":[],"children":[{"type":"declaration","line":2,"var_name":"n","type_name":"int","full_type":"int","container":null,"init":"a.size()","exprs":[{"type":"call","line":2,"callee":"size","receiver":"a","args":[],"is_recursive":false}]},{"type":"loop","kind":"for","line":3,"end_line":7,"init":"int i = 0","cond":"i < n","inc":"i++","exprs":[],"children":[{"type":"loop","kind":"for","line":4,"end_line":6,"init":"int j = i + 1","cond":"j < n","inc":"j++","exprs":[],"children":[{"type":"branch","kind":"if","line":5,"end_line":5,"cond":"a[i] + a[j] == k","exprs":[{"type":"array_access","line":5,"base":"a","index":"i"},{"type":"array_access","line":5,"base":"a","index":"j"}],"children":[{"type":"return","line":5,"value":"true","exprs":[]}],"else_children":[]}]}]},{"type":"return","line":8,"value":"false","exprs":[]}]}]}})json";
const char* const kSampleCfgJson = R"json({"schema_version":1,"functions":[{"name":"hasPair","entry":0,"exit":10,"blocks":[{"id":0,"kind":"entry","lines":[1]},{"id":1,"kind":"basic","lines":[2,3]},{"id":2,"kind":"loop_cond","lines":[3]},{"id":3,"kind":"basic","lines":[4]},{"id":4,"kind":"loop_cond","lines":[4]},{"id":5,"kind":"branch","lines":[5]},{"id":6,"kind":"return","lines":[5]},{"id":7,"kind":"loop_inc","lines":[4]},{"id":8,"kind":"loop_inc","lines":[3]},{"id":9,"kind":"return","lines":[8]},{"id":10,"kind":"exit","lines":[]}],"edges":[{"from":0,"to":1,"kind":"next"},{"from":1,"to":2,"kind":"next"},{"from":2,"to":3,"kind":"true"},{"from":2,"to":9,"kind":"false"},{"from":3,"to":4,"kind":"next"},{"from":4,"to":5,"kind":"true"},{"from":4,"to":8,"kind":"false"},{"from":5,"to":6,"kind":"true"},{"from":5,"to":7,"kind":"false"},{"from":6,"to":10,"kind":"next"},{"from":7,"to":4,"kind":"back"},{"from":8,"to":2,"kind":"back"},{"from":9,"to":10,"kind":"next"}]}]})json";

bool has(const std::string& code, const char* marker) {
    return code.find(marker) != std::string::npos;
}

AnalysisResult failed(const std::string& error) {
    AnalysisResult r;
    r.success = false;
    r.error = error;
    return r;
}

// Spreads total_delay across the checkpoints (api-spec section 10: about 3 s).
// Returns false if cancelled mid-step.
bool stepThrough(const std::vector<std::pair<int, std::string>>& steps,
                 std::chrono::milliseconds total_delay,
                 const ProgressFn& on_progress,
                 const std::atomic<bool>& cancelled) {
    const auto delay = total_delay / static_cast<int>(steps.size());
    for (const auto& [percent, stage] : steps) {
        if (cancelled.load()) return false;
        std::this_thread::sleep_for(delay);
        if (on_progress) on_progress(percent, stage);
    }
    return true;
}

} // namespace

AnalysisResult EngineStub::fakeAnalysis(const std::string& code,
                                        const ProblemSpec& /*spec*/,
                                        ProgressFn on_progress) {
    if (!stepThrough({
            {10, "clang AST"},
            {20, "internal AST"},
            {30, "control flow graph"},
            {45, "complexity analysis"},
            {55, "feature extraction"},
            {65, "algorithm classification"},
            {75, "static checks"},
            {90, "differential testing"},
        }, total_delay_, on_progress, cancelled_)) {
        return failed("cancelled");
    }

    if (has(code, "// STUB:compile_error"))
        return failed("COMPILE_ERROR: line 7: expected ';' before '}'");
    if (has(code, "// STUB:timeout"))
        return failed("TIMEOUT: execution exceeded 5000 ms");

    AnalysisResult result;
    result.ast_json = kSampleAstJson;
    result.cfg_json = kSampleCfgJson;

    try {
        const auto features = predictor_.extractFeatures(result.ast_json, result.cfg_json);
        result.algorithms = predictor_.predict(features, 3);
    } catch (const std::exception& e) {
        return failed(std::string("INTERNAL: ") + e.what());
    }
    if (result.algorithms.empty())
        return failed("MODEL_UNAVAILABLE: no active model");

    result.complexity.time = "O(n^2)";
    result.complexity.space = "O(1)";
    result.complexity.derivation = {
        "outer loop runs n times (line 3)",
        "inner loop runs n - i - 1 times (line 4)",
        "sum over i gives n(n-1)/2",
        "no heap allocation detected",
    };

    result.findings = {
        {5, "medium", "overflow_risk",
         "a[i] + a[j] may overflow int for values near INT_MAX"},
    };

    result.counterexamples = {
        {"a = [1, 3, 5]\nk = 8", "true", "false"},
    };

    result.optimization_available = true;
    result.success = true;
    return result;
}

AnalysisResult EngineStub::analyze(const std::string& code,
                                   const ProblemSpec& spec,
                                   ProgressFn on_progress) {
    AnalysisResult result = fakeAnalysis(code, spec, on_progress);
    if (result.success && on_progress) on_progress(100, "complete");
    return result;
}

OptimizeResult EngineStub::optimize(const std::string& code,
                                    const ProblemSpec& spec,
                                    ProgressFn on_progress) {
    OptimizeResult result;
    result.analysis = fakeAnalysis(code, spec, on_progress);

    if (!result.analysis.success) {
        result.success = false;
        result.error = result.analysis.error;
        return result;
    }

    if (cancelled_.load()) {
        result.success = false;
        result.error = "cancelled";
        return result;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    if (on_progress) on_progress(100, "optimization");

    result.recommended_algorithm = "hash_set_lookup";
    result.recommended_complexity = "O(n)";

    // api-spec rendering rule: never expose unverified code or a summary.
    if (has(code, "// STUB:unverified")) {
        result.verified = false;
        result.success = true;
        return result;           // optimized_code and summary stay empty
    }

    result.optimized_code =
        "bool hasPair(vector<int>& a, int k) {\n"
        "    unordered_set<int> seen;\n"
        "    for (int x : a) {\n"
        "        if (seen.count(k - x)) return true;\n"
        "        seen.insert(x);\n"
        "    }\n"
        "    return false;\n"
        "}";

    result.summary.headline = "Replaced the inner scan with a hash set lookup.";
    result.summary.explanation =
        "The original checks every pair, so the work grows with the square "
        "of the input size. The new version stores each value as it passes "
        "and asks the set whether the complement k - x has already been "
        "seen, which answers the same question in one pass.";
    result.summary.comparison = {
        {"Algorithm",            "Brute force pair search", "Hash set lookup"},
        {"Time",                 "O(n^2)",  "O(n) expected"},
        {"Space",                "O(1)",    "O(n)"},
        {"Runtime at n = 50000", "2841 ms", "8.4 ms"},
        {"Memory",               "412 KB",  "2180 KB"},
    };
    result.summary.changes = {
        "Removed the nested loop over j (lines 4 to 6)",
        "Added an unordered_set<int> seen to record values already visited",
        "Replaced the a[i] + a[j] == k test with a complement lookup",
    };
    result.summary.tradeoff =
        "Memory rises from constant to linear in n. At the stated bound of "
        "n = 100000 this is roughly 400 KB, which is acceptable.";
    result.summary.verification =
        "Compiled successfully and produced identical output to the "
        "original on 200 generated inputs, including empty array, single "
        "element, all-equal values, and values near INT_MAX.";
    result.summary.speedup = 338.2;

    result.verified = true;

    result.bench.n_used = 50000;
    result.bench.before_ms = 2841.3;
    result.bench.after_ms = 8.4;
    result.bench.before_kb = 412;
    result.bench.after_kb = 2180;

    if (has(code, "// STUB:nospeedup")) {
        result.summary.speedup = 0.0;
        result.summary.tradeoff.clear();
    }

    result.success = true;
    return result;
}

void EngineStub::cancel() {
    cancelled_.store(true);
}

} // namespace nc