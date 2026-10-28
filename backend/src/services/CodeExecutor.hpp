#pragma once
// Runs POST /execute requests off the HTTP threads, with a cap on how many can be waiting.
// The actual compile-and-run is an ExecuteFn: a stub now, T4's sandbox (Compiler + Runner)
// when it is wired in. Each execution blocks a worker for up to ~15 s (10 s compile + run),
// so this has its own small pool and never borrows the job workers.

#include <atomic>
#include <cstddef>
#include <functional>

#include "common/Types.hpp"
#include "services/ThreadPool.hpp"

namespace nc {

class CodeExecutor {
public:
    using Done = std::function<void(ExecuteOutcome)>;

    CodeExecutor(ExecuteFn fn, std::size_t workers, std::size_t maxPending);

    // Returns false (and does nothing) when maxPending executions are already queued or
    // running. `done` is called on a worker thread.
    bool submit(ExecuteRequest req, Done done);

private:
    ExecuteFn fn_;
    std::size_t maxPending_;
    std::atomic<std::size_t> pending_{0};
    ThreadPool pool_;   // last: joins first on destruction
};

// Placeholder until the sandbox is connected: reports that nothing was run.
ExecuteFn makeStubExecuteFn();

}  // namespace nc
