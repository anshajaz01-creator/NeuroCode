#pragma once
#include <string>
#include <vector>

#include "sandbox/Limits.hpp"

namespace nc {

enum class RunStatus {
    ok,            // exited with code 0
    nonzero_exit,  // exited with a non-zero code
    signaled,      // killed by a signal (crash, memory limit, CPU limit, SIGXFSZ ...)
    timed_out,     // wall timer expired, killed by the parent
    output_limit,  // wrote more than Limits::output_bytes, killed by the parent
    start_failed   // fork, pipe or exec failed (error says why): report SANDBOX_ERROR
};

const char* toString(RunStatus s);

struct RunResult {
    RunStatus   status = RunStatus::start_failed;
    int         exit_code = -1;       // valid for ok / nonzero_exit
    int         term_signal = 0;      // valid for signaled (SIGKILL after a timeout)
    std::string stdout_text;
    std::string stderr_text;
    bool        stdout_truncated = false;
    bool        stderr_truncated = false;
    double      wall_ms = 0;          // elapsed, measured by the parent
    double      cpu_ms = 0;           // user + system time of the child
    long        peak_kb = 0;          // peak resident memory of the child itself, in KB. 0 means too short
                                      // to measure (see Runner.cpp), not zero memory
    std::string error;                // set for start_failed
};

// Runs argv[0] with the given arguments in its own process group, with stdin fed from
// stdin_text and stdout/stderr captured. cwd is entered before exec when non-empty.
// env holds "NAME=value" strings and replaces the environment completely.
// Thread safe: call it from any number of worker threads. Blocks until the child is gone.
RunResult runProcess(const std::vector<std::string>& argv,
                     const std::string& stdin_text,
                     const Limits& limits,
                     const std::string& cwd = "",
                     const std::vector<std::string>& env = {});

// Convenience for a compiled user binary: no arguments, empty environment.
RunResult runBinary(const std::string& binary_path,
                    const std::string& stdin_text,
                    const Limits& limits,
                    const std::string& cwd = "");

} // namespace nc
