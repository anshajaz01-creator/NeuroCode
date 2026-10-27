#pragma once
#include <string>
#include <vector>

namespace nc {

struct AlgorithmGuess { std::string label; float probability = 0.0f; };

struct Complexity {
    std::string time;                      // "O(n^2)"
    std::string space;                     // "O(1)"
    std::vector<std::string> derivation;   // human readable steps
};

struct Finding {
    int line = 0;
    std::string severity;   // "high" | "medium" | "low"
    std::string type;       // "unreachable", "overflow_risk", ...
    std::string message;
};

struct Counterexample {
    std::string input;
    std::string expected_output;
    std::string actual_output;
};

struct AnalysisResult {
    std::vector<AlgorithmGuess> algorithms;   // ranked, top 3
    Complexity complexity;
    std::vector<Finding> findings;
    std::vector<Counterexample> counterexamples;
    std::string ast_json;
    std::string cfg_json;
    bool optimization_available = false;
    bool success = true;
    std::string error;
};

} // namespace nc