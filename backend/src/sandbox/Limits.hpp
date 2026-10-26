#pragma once
#include <cstddef>

namespace nc {

// Resource limits for one sandboxed process. Defaults match architecture.md
// section 9 for running user code.
struct Limits {
    int         cpu_seconds         = 5;          // RLIMIT_CPU, backstop for the wall timer
    int         wall_ms             = 5000;       // parent SIGKILLs the process group after this
    std::size_t address_space_bytes = 256u << 20; // RLIMIT_AS, 0 = unlimited
    std::size_t output_bytes        = 1u << 20;   // per stream (stdout, stderr), enforced by the parent
    std::size_t file_write_bytes    = 0;          // RLIMIT_FSIZE, 0 = no file writes
    int         max_processes       = 1;          // RLIMIT_NPROC, 0 = unlimited (see note)
    int         run_as_uid          = -1;         // drop to this uid if running as root, -1 = keep
    bool        isolate_network     = true;       // best effort: unshare(CLONE_NEWNET), ignored if refused

    // Note on max_processes: RLIMIT_NPROC counts every process of the same uid and is
    // not enforced for root. It only stops fork bombs when the sandbox runs as an
    // unprivileged user, so set run_as_uid when the server runs as root.

    static Limits forRun(int timeout_ms = 5000);   // analysis and /execute
    static Limits forBenchmark();                  // 10 s CPU and wall
    static Limits forCompile();                    // g++ and its children, 10 s, 64 KB of diagnostics
};

// Applies the limits to the calling process. Intended for the child between fork()
// and exec(), so it only makes raw system calls: no allocation, no locks.
// Returns false if a mandatory limit could not be set (the child then exits).
bool applyLimits(const Limits& limits);

} // namespace nc
