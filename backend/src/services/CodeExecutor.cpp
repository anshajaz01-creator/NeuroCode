#include "services/CodeExecutor.hpp"

#include <exception>

#include "common/Logger.hpp"

namespace nc {

CodeExecutor::CodeExecutor(ExecuteFn fn, std::size_t workers, std::size_t maxPending)
    : fn_(std::move(fn)), maxPending_(maxPending), pool_(workers) {}

bool CodeExecutor::submit(ExecuteRequest req, Done done) {
    std::size_t cur = pending_.load();
    do {
        if (cur >= maxPending_) return false;
    } while (!pending_.compare_exchange_weak(cur, cur + 1));

    pool_.submit([this, req = std::move(req), done = std::move(done)]() mutable {
        ExecuteOutcome out;
        try {
            out = fn_(req);
        } catch (const std::exception& e) {
            NC_LOG_ERROR << "execute threw: " << e.what();
            out = ExecuteOutcome{};
            out.compile_error = "internal sandbox error";
        } catch (...) {
            out = ExecuteOutcome{};
            out.compile_error = "internal sandbox error";
        }
        --pending_;
        done(std::move(out));
    });
    return true;
}

ExecuteFn makeStubExecuteFn() {
    return [](const ExecuteRequest&) {
        ExecuteOutcome o;
        o.success = false;
        o.compile_error = "sandbox is not connected yet (stub executor): your code was not run";
        return o;
    };
}

}  // namespace nc
