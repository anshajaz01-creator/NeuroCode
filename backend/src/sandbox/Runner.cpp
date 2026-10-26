#include "sandbox/Runner.hpp"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <poll.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

namespace nc {

const char* toString(RunStatus s) {
    switch (s) {
        case RunStatus::ok:           return "ok";
        case RunStatus::nonzero_exit: return "nonzero_exit";
        case RunStatus::signaled:     return "signaled";
        case RunStatus::timed_out:    return "timed_out";
        case RunStatus::output_limit: return "output_limit";
        case RunStatus::start_failed: return "start_failed";
    }
    return "start_failed";
}

namespace {

using Clock = std::chrono::steady_clock;

class Fd {
public:
    Fd() = default;
    explicit Fd(int fd) : fd_(fd) {}
    Fd(const Fd&) = delete;
    Fd& operator=(const Fd&) = delete;
    Fd(Fd&& o) noexcept : fd_(o.release()) {}
    Fd& operator=(Fd&& o) noexcept { reset(o.release()); return *this; }
    ~Fd() { reset(); }
    int get() const { return fd_; }
    bool valid() const { return fd_ >= 0; }
    int release() { int f = fd_; fd_ = -1; return f; }
    void reset(int fd = -1) { if (fd_ >= 0) ::close(fd_); fd_ = fd; }
private:
    int fd_ = -1;
};

// Moves fd to a number >= 10 so it can never collide with 0, 1, 2 when the child
// rearranges its descriptors, and keeps it close-on-exec.
Fd highFd(int fd) {
    if (fd < 0) return Fd();
    const int moved = fcntl(fd, F_DUPFD_CLOEXEC, 10);
    const int e = errno;
    ::close(fd);
    errno = e;
    return Fd(moved);
}

bool makePipe(Fd& rd, Fd& wr) {
    int p[2];
    if (pipe2(p, O_CLOEXEC) != 0) return false;
    rd = highFd(p[0]);
    wr = highFd(p[1]);
    return rd.valid() && wr.valid();
}

void setNonBlocking(int fd) {
    const int fl = fcntl(fd, F_GETFL, 0);
    if (fl >= 0) fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

std::string resolveExecutable(const std::string& name, const std::vector<std::string>& env) {
    if (name.find('/') != std::string::npos) return name;
    std::string path = "/usr/local/bin:/usr/bin:/bin";
    for (const auto& e : env)
        if (e.rfind("PATH=", 0) == 0) path = e.substr(5);
    std::size_t start = 0;
    while (start <= path.size()) {
        std::size_t end = path.find(':', start);
        if (end == std::string::npos) end = path.size();
        const std::string dir = path.substr(start, end - start);
        const std::string candidate = (dir.empty() ? "." : dir) + "/" + name;
        if (access(candidate.c_str(), X_OK) == 0) return candidate;
        start = end + 1;
    }
    return "";
}

// Resident memory of this process in KB, from /proc/self/statm. 0 if unavailable.
long selfRssKb() {
    char buf[128];
    const int fd = open("/proc/self/statm", O_RDONLY | O_CLOEXEC);
    if (fd < 0) return 0;
    const ssize_t n = read(fd, buf, sizeof(buf) - 1);
    ::close(fd);
    if (n <= 0) return 0;
    buf[n] = '\0';
    long size = 0, resident = 0;
    if (sscanf(buf, "%ld %ld", &size, &resident) != 2) return 0;
    return resident * (sysconf(_SC_PAGESIZE) / 1024);
}

// Peak resident memory of a live process (VmHWM). It belongs to the process's current
// address space, so it starts from zero at exec. 0 if the process is gone.
long vmHwmKb(pid_t pid) {
    char path[48];
    snprintf(path, sizeof(path), "/proc/%d/status", static_cast<int>(pid));
    const int fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd < 0) return 0;
    char buf[4096];
    const ssize_t n = read(fd, buf, sizeof(buf) - 1);
    ::close(fd);
    if (n <= 0) return 0;
    buf[n] = '\0';
    const char* p = strstr(buf, "VmHWM:");
    return p ? strtol(p + 6, nullptr, 10) : 0;
}

// Child side, after fork(). Only async-signal-safe calls: the parent may have other
// threads holding the allocator lock at the moment of the fork.
[[noreturn]] void childFail(int err_fd, int code) {
    const int e = code;
    ssize_t ignored = write(err_fd, &e, sizeof(e));
    (void)ignored;
    _exit(127);
}

void closeAllExcept(int keep) {
#ifdef SYS_close_range
    bool ok = true;
    if (keep > 3) ok = syscall(SYS_close_range, 3u, static_cast<unsigned>(keep - 1), 0u) == 0;
    ok = ok && syscall(SYS_close_range, static_cast<unsigned>(keep + 1), ~0u, 0u) == 0;
    if (ok) return;
#endif
    for (int fd = 3; fd < 4096; ++fd)
        if (fd != keep) ::close(fd);
}

double ms(Clock::time_point a, Clock::time_point b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
}

} // namespace

RunResult runProcess(const std::vector<std::string>& argv,
                     const std::string& stdin_text,
                     const Limits& limits,
                     const std::string& cwd,
                     const std::vector<std::string>& env) {
    RunResult res;
    auto fail = [&](const std::string& why) { res.status = RunStatus::start_failed; res.error = why; return res; };

    if (argv.empty()) return fail("empty argv");
    const std::string exe = resolveExecutable(argv[0], env);
    if (exe.empty()) return fail("executable not found: " + argv[0]);

    // Everything the child needs is built before fork().
    std::vector<char*> c_argv;
    for (const auto& a : argv) c_argv.push_back(const_cast<char*>(a.c_str()));
    c_argv.push_back(nullptr);
    std::vector<char*> c_env;
    for (const auto& e : env) c_env.push_back(const_cast<char*>(e.c_str()));
    c_env.push_back(nullptr);
    const char* c_cwd = cwd.empty() ? nullptr : cwd.c_str();
    const unsigned alarm_s = static_cast<unsigned>(limits.wall_ms / 1000 + 2);   // second line of defence

    Fd out_r, out_w, err_r, err_w, status_r, status_w;
    if (!makePipe(out_r, out_w) || !makePipe(err_r, err_w) || !makePipe(status_r, status_w))
        return fail(std::string("pipe: ") + strerror(errno));

    int sv[2];
    if (socketpair(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0, sv) != 0)
        return fail(std::string("socketpair: ") + strerror(errno));
    Fd in_parent = highFd(sv[0]);
    Fd in_child = highFd(sv[1]);
    if (!in_parent.valid() || !in_child.valid()) return fail("descriptor setup failed");

    const long baseline_kb = selfRssKb();
    const auto start = Clock::now();

    const pid_t pid = fork();
    if (pid < 0) return fail(std::string("fork: ") + strerror(errno));

    if (pid == 0) {
        const int ef = status_w.get();
        setpgid(0, 0);                                    // own group, so the parent can kill descendants too
        sigset_t none;
        sigemptyset(&none);
        sigprocmask(SIG_SETMASK, &none, nullptr);
        if (c_cwd && chdir(c_cwd) != 0) childFail(ef, errno);
        if (dup2(in_child.get(), 0) < 0 || dup2(out_w.get(), 1) < 0 || dup2(err_w.get(), 2) < 0)
            childFail(ef, errno);
        closeAllExcept(ef);
        if (!applyLimits(limits)) childFail(ef, EPERM);
        alarm(alarm_s);
        execve(exe.c_str(), c_argv.data(), c_env.data());
        childFail(ef, errno);
    }

    setpgid(pid, pid);                                    // also from the parent, to close the race
    out_w.reset(); err_w.reset(); status_w.reset(); in_child.reset();

    // exec succeeded when the close-on-exec pipe reaches EOF without data.
    int child_errno = 0;
    ssize_t got;
    do { got = read(status_r.get(), &child_errno, sizeof(child_errno)); } while (got < 0 && errno == EINTR);
    status_r.reset();
    if (got == static_cast<ssize_t>(sizeof(child_errno))) {
        int st = 0;
        waitpid(pid, &st, 0);
        return fail(std::string("exec ") + argv[0] + ": " + strerror(child_errno));
    }

    setNonBlocking(out_r.get());
    setNonBlocking(err_r.get());
    setNonBlocking(in_parent.get());

    const auto deadline = start + std::chrono::milliseconds(limits.wall_ms);
    std::size_t in_off = 0;
    bool in_open = true;
    bool exited = false, killed = false, timed_out = false, flooded = false;
    int status = 0;
    rusage ru{};
    long polled_kb = vmHwmKb(pid);   // first sample straight after exec

    auto killGroup = [&] {
        if (!killed) { kill(-pid, SIGKILL); killed = true; }
    };
    auto closeStdin = [&] {
        if (in_open) { shutdown(in_parent.get(), SHUT_WR); in_open = false; in_parent.reset(); }
    };
    // Reads whatever is available; returns false once the stream hit EOF.
    auto drain = [&](Fd& fd, std::string& dst, bool& truncated) {
        char buf[65536];
        while (fd.valid()) {
            const ssize_t n = read(fd.get(), buf, sizeof(buf));
            if (n > 0) {
                const std::size_t room = limits.output_bytes > dst.size() ? limits.output_bytes - dst.size() : 0;
                const std::size_t take = std::min<std::size_t>(room, static_cast<std::size_t>(n));
                dst.append(buf, take);
                if (take < static_cast<std::size_t>(n)) { truncated = true; flooded = true; }
            } else if (n == 0) {
                fd.reset();
            } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            } else if (errno != EINTR) {
                fd.reset();
            }
        }
    };

    if (stdin_text.empty()) closeStdin();

    try {
        while (true) {
            struct pollfd fds[3];
            int nfds = 0;
            int idx_out = -1, idx_err = -1, idx_in = -1;
            if (out_r.valid()) { idx_out = nfds; fds[nfds++] = {out_r.get(), POLLIN, 0}; }
            if (err_r.valid()) { idx_err = nfds; fds[nfds++] = {err_r.get(), POLLIN, 0}; }
            if (in_open && in_parent.valid()) { idx_in = nfds; fds[nfds++] = {in_parent.get(), POLLOUT, 0}; }

            // Short ticks at first so the memory sampler sees short programs.
            const double elapsed = ms(start, Clock::now());
            const int tick = elapsed < 100 ? 1 : 5;
            poll(fds, static_cast<nfds_t>(nfds), tick);

            if (idx_out >= 0 && (fds[idx_out].revents & (POLLIN | POLLHUP | POLLERR))) drain(out_r, res.stdout_text, res.stdout_truncated);
            if (idx_err >= 0 && (fds[idx_err].revents & (POLLIN | POLLHUP | POLLERR))) drain(err_r, res.stderr_text, res.stderr_truncated);
            if (idx_in >= 0 && (fds[idx_in].revents & (POLLOUT | POLLERR | POLLHUP))) {
                const ssize_t n = send(in_parent.get(), stdin_text.data() + in_off,
                                       stdin_text.size() - in_off, MSG_NOSIGNAL);
                if (n > 0) in_off += static_cast<std::size_t>(n);
                else if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) in_off = stdin_text.size();
                if (in_off >= stdin_text.size()) closeStdin();
            }

            if (!exited) {
                const pid_t w = wait4(pid, &status, WNOHANG, &ru);
                if (w == pid) exited = true;
                else if (w < 0 && errno != EINTR) { exited = true; status = 0; }
                else polled_kb = std::max(polled_kb, vmHwmKb(pid));
            }
            if (!exited && !killed) {
                if (flooded) killGroup();
                else if (Clock::now() >= deadline) { timed_out = true; killGroup(); }
            }
            if (exited) {
                drain(out_r, res.stdout_text, res.stdout_truncated);   // pick up what is already in the pipes
                drain(err_r, res.stderr_text, res.stderr_truncated);
                break;
            }
        }
    } catch (...) {
        kill(-pid, SIGKILL);
        waitpid(pid, &status, 0);
        return fail("internal error while supervising the process");
    }
    kill(-pid, SIGKILL);   // anything the process left behind in its group

    res.wall_ms = ms(start, Clock::now());
    res.cpu_ms = ru.ru_utime.tv_sec * 1e3 + ru.ru_utime.tv_usec / 1e3 +
                 ru.ru_stime.tv_sec * 1e3 + ru.ru_stime.tv_usec / 1e3;

    // ru_maxrss of a forked child never drops below the parent's resident size at fork time
    // (the kernel carries the old address space's high-water mark across exec), so a small
    // program started from a large server would report the server's size. Trust it only when it
    // clearly exceeds that floor. Otherwise use the sampled VmHWM, which starts from zero at exec.
    // A program that ends before the first sample, started from a large server, cannot be measured
    // and reports 0 rather than the server's size.
    const long slack_kb = std::max<long>(1024, baseline_kb / 50);
    const long ru_kb = ru.ru_maxrss;
    res.peak_kb = ru_kb > baseline_kb + slack_kb ? std::max(ru_kb, polled_kb) : polled_kb;

    if (WIFEXITED(status)) {
        res.exit_code = WEXITSTATUS(status);
        res.status = res.exit_code == 0 ? RunStatus::ok : RunStatus::nonzero_exit;
    } else if (WIFSIGNALED(status)) {
        res.term_signal = WTERMSIG(status);
        if ((timed_out && res.term_signal == SIGKILL) || res.term_signal == SIGXCPU) res.status = RunStatus::timed_out;
        else if (flooded && res.term_signal == SIGKILL) res.status = RunStatus::output_limit;
        else res.status = RunStatus::signaled;
    }
    return res;
}

RunResult runBinary(const std::string& binary_path, const std::string& stdin_text,
                    const Limits& limits, const std::string& cwd) {
    return runProcess({binary_path}, stdin_text, limits, cwd, {});
}

} // namespace nc
