#include "sandbox/Limits.hpp"

#include <sched.h>
#include <sys/resource.h>
#include <grp.h>
#include <unistd.h>

namespace nc {

Limits Limits::forRun(int timeout_ms) {
    Limits l;
    l.wall_ms = timeout_ms;
    l.cpu_seconds = timeout_ms / 1000 + 1;   // backstop one second after the wall timer
    return l;
}

Limits Limits::forBenchmark() {
    Limits l;
    l.cpu_seconds = 10;
    l.wall_ms = 10000;
    return l;
}

Limits Limits::forCompile() {
    Limits l;
    l.cpu_seconds = 10;
    l.wall_ms = 10000;
    l.address_space_bytes = std::size_t(2) << 30;   // cc1plus on <bits/stdc++.h> needs a few hundred MB
    l.output_bytes = 64u << 10;
    l.file_write_bytes = std::size_t(64) << 20;     // the compiler writes the binary
    l.max_processes = 0;                            // g++ spawns cc1plus, as and ld
    return l;
}

namespace {
bool setLimit(int resource, rlim_t value) {
    const rlimit r{value, value};
    return setrlimit(resource, &r) == 0;
}
} // namespace

bool applyLimits(const Limits& l) {
    if (!setLimit(RLIMIT_CORE, 0)) return false;
    if (!setLimit(RLIMIT_CPU, static_cast<rlim_t>(l.cpu_seconds))) return false;
    if (l.address_space_bytes && !setLimit(RLIMIT_AS, l.address_space_bytes)) return false;
    if (!setLimit(RLIMIT_FSIZE, l.file_write_bytes)) return false;

    if (l.isolate_network) (void)unshare(CLONE_NEWNET);   // best effort, needs privileges

    // Drop privileges before RLIMIT_NPROC so the limit counts against the new uid.
    if (l.run_as_uid >= 0 && geteuid() == 0) {
        const gid_t gid = static_cast<gid_t>(l.run_as_uid);
        if (setgroups(0, nullptr) != 0 || setgid(gid) != 0 ||
            setuid(static_cast<uid_t>(l.run_as_uid)) != 0)
            return false;
    }
    if (l.max_processes > 0 && !setLimit(RLIMIT_NPROC, static_cast<rlim_t>(l.max_processes)))
        return false;
    return true;
}

} // namespace nc
