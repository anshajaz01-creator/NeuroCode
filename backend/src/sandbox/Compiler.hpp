#pragma once
#include <string>

#include "sandbox/Limits.hpp"

namespace nc {

// User code is submitted without includes (api-spec sample uses vector<int> and
// unordered_set directly). This preamble is prepended everywhere user code is parsed or
// compiled (libclang, sandbox, benchmark, the Python extractor) so the trees never drift.
inline constexpr const char* kUserPreamble = "#include <bits/stdc++.h>\nusing namespace std;\n";

// preamble + "#line 1" + user code, so compiler messages carry the user's own line numbers.
// Append any harness (main, test driver) AFTER the user code to keep those numbers valid.
std::string wrapUserSource(const std::string& user_code);

struct CompileResult {
    bool        ok = false;
    std::string binary_path;       // set when ok
    std::string error_summary;     // "line 7: expected ';' before '}'" for the COMPILE_ERROR message
    std::string error_full;        // trimmed compiler output, scratch paths removed
    bool        timed_out = false; // compiler exceeded Limits::wall_ms
    bool        sandbox_error = false; // g++ missing or could not be started: report SANDBOX_ERROR
};

// Writes `source` into work_dir and builds it with g++ -std=c++17 -O2.
// `limits` defaults to Limits::forCompile(); pass run_as_uid through it when the server runs as root.
CompileResult compileCpp(const std::string& source,
                         const std::string& work_dir,
                         const std::string& name = "prog",
                         const Limits& limits = Limits::forCompile());

// Exposed for tests: pulls the first "file:LINE:COL: error: message" out of g++ output.
std::string summarizeCompileError(const std::string& compiler_output);

} // namespace nc
