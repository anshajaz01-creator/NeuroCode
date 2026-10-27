// Sandbox tests. Plain checks, no framework. Build from backend/:
//   g++ -std=c++20 -I src src/sandbox/*.cpp tests/test_sandbox.cpp -o test_sandbox -pthread
// Run as root or as a normal user. As root the process-limit tests drop to uid 65534.
#include <sys/stat.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

#include "sandbox/Compiler.hpp"
#include "sandbox/Runner.hpp"
#include "sandbox/ScratchDir.hpp"

using namespace nc;

static int g_fail = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) { ++g_fail; std::cerr << "FAIL line " << __LINE__ << ": " #cond "\n"; } \
    } while (0)

static const int kUid = geteuid() == 0 ? 65534 : -1;   // sandbox user when running as root

static Limits runLimits(int wall_ms = 5000) {
    Limits l = Limits::forRun(wall_ms);
    l.run_as_uid = kUid;
    return l;
}

static std::string build(ScratchDir& dir, const std::string& src, const std::string& name = "prog") {
    Limits cl = Limits::forCompile();
    cl.run_as_uid = kUid;
    const CompileResult c = compileCpp(src, dir.path(), name, cl);
    if (!c.ok) std::cerr << "build failed: " << c.error_full << "\n";
    CHECK(c.ok);
    return c.binary_path;
}

static double since(std::chrono::steady_clock::time_point t) {
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t).count();
}

int main() {
    ScratchDir dir(kUid);

    // --- 1. normal run: stdin in, stdout out, metrics filled
    const std::string sum = build(dir, R"(#include <iostream>
int main(){ long long a,b; std::cin >> a >> b; std::cout << a+b << "\n"; })", "sum");
    {
        RunResult r = runBinary(sum, "20 22\n", runLimits(), dir.path());
        CHECK(r.status == RunStatus::ok && r.exit_code == 0);
        CHECK(r.stdout_text == "42\n");
        CHECK(r.wall_ms > 0 && r.peak_kb > 0);
    }

    // --- 2. compile error: user line numbers survive the preamble
    {
        ScratchDir d2(kUid);
        const std::string bad = wrapUserSource("int main() {\n    int x = 1\n    return x;\n}\n");
        Limits cl = Limits::forCompile(); cl.run_as_uid = kUid;
        CompileResult c = compileCpp(bad, d2.path(), "bad", cl);
        CHECK(!c.ok && !c.timed_out && !c.sandbox_error);
        CHECK(c.error_summary.rfind("line 3:", 0) == 0);            // g++ reports the token after the missing ';'
        CHECK(c.error_full.find(d2.path()) == std::string::npos);   // no scratch paths leak
        std::cout << "  compile error summary: " << c.error_summary << "\n";

        // Unambiguous line mapping: the preamble adds two lines, user.cpp must still say line 2.
        const std::string undeclared = wrapUserSource("int main() {\n    return undefined_name;\n}\n");
        CompileResult u = compileCpp(undeclared, d2.path(), "undeclared", cl);
        CHECK(!u.ok && u.error_summary.rfind("line 2:", 0) == 0);
        CHECK(u.error_summary.find("undefined_name") != std::string::npos);
    }

    // --- 3. infinite loop is killed
    {
        const std::string spin = build(dir, "int main(){ volatile unsigned long x=0; for(;;) x++; }", "spin");
        auto t = std::chrono::steady_clock::now();
        RunResult r = runBinary(spin, "", runLimits(1000), dir.path());
        CHECK(r.status == RunStatus::timed_out);
        CHECK(since(t) < 2500);
    }

    // --- 4. sleeping forever (no CPU) is killed by the wall timer
    {
        const std::string nap = build(dir, "#include <unistd.h>\nint main(){ sleep(60); }", "nap");
        auto t = std::chrono::steady_clock::now();
        RunResult r = runBinary(nap, "", runLimits(500), dir.path());
        CHECK(r.status == RunStatus::timed_out);
        CHECK(since(t) < 1500);
    }

    // --- 5. memory bomb stays inside the address-space limit
    {
        const std::string bomb = build(dir, "#include <vector>\nint main(){ std::vector<char> v(1u<<30, 1); return v[100]; }", "bomb");
        RunResult r = runBinary(bomb, "", runLimits(), dir.path());
        CHECK(r.status == RunStatus::signaled || r.status == RunStatus::nonzero_exit);
        CHECK(r.stderr_text.find("bad_alloc") != std::string::npos);
        CHECK(r.peak_kb < 300 * 1024);
    }

    // --- 6. output flood is cut at the cap and the process is killed
    {
        const std::string flood = build(dir, "#include <cstdio>\nint main(){ for(;;) puts(\"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\"); }", "flood");
        RunResult r = runBinary(flood, "", runLimits(), dir.path());
        CHECK(r.status == RunStatus::output_limit);
        CHECK(r.stdout_truncated && r.stdout_text.size() == Limits{}.output_bytes);
    }

    // --- 7. no file writes
    {
        const std::string writer = build(dir, R"(#include <cstdio>
int main(){ FILE* f = fopen("out.txt","w"); if(!f) return 3; fputs("hello", f); return fclose(f) == 0 ? 0 : 4; })", "writer");
        RunResult r = runBinary(writer, "", runLimits(), dir.path());
        CHECK(r.status != RunStatus::ok);
        struct stat st{};
        const bool empty_or_absent = stat((dir.path() + "/out.txt").c_str(), &st) != 0 || st.st_size == 0;
        CHECK(empty_or_absent);
    }

    // --- 8. process limit stops fork (only meaningful for a non-root uid)
    if (kUid >= 0) {
        const std::string forker = build(dir, "#include <unistd.h>\nint main(){ pid_t p = fork(); if (p < 0) return 42; if (p == 0) _exit(0); return 0; }", "forker");
        RunResult r = runBinary(forker, "", runLimits(), dir.path());
        CHECK(r.status == RunStatus::nonzero_exit && r.exit_code == 42);
    } else {
        std::cout << "  SKIP fork test (needs root to drop privileges)\n";
    }

    // --- 9. stdin: 900 KB echoed back, and a 5 MB write to a program that never reads
    {
        const std::string echo = build(dir, "#include <iostream>\nint main(){ std::cout << std::cin.rdbuf(); }", "echo");
        std::string big(900 * 1024, 'a');
        for (std::size_t i = 0; i < big.size(); i += 61) big[i] = '\n';
        RunResult r = runBinary(echo, big, runLimits(), dir.path());
        CHECK(r.status == RunStatus::ok && r.stdout_text == big);

        const std::string deaf = build(dir, "int main(){ return 0; }", "deaf");
        auto t = std::chrono::steady_clock::now();
        RunResult d = runBinary(deaf, std::string(5 << 20, 'x'), runLimits(), dir.path());
        CHECK(d.status == RunStatus::ok);
        CHECK(since(t) < 1500);
    }

    // --- 10. cwd and a scrubbed environment
    {
        const std::string probe = build(dir, R"(#include <cstdio>
#include <cstdlib>
#include <unistd.h>
int main(){ char b[512]; if(!getcwd(b, sizeof b)) return 1; puts(b); puts(getenv("HOME") ? "has-home" : "no-home"); })", "probe");
        RunResult r = runBinary(probe, "", runLimits(), dir.path());
        CHECK(r.status == RunStatus::ok);
        CHECK(r.stdout_text.find(dir.path()) == 0 && r.stdout_text.find("no-home") != std::string::npos);
    }

    // --- 11. exec failure is reported, not hung
    {
        RunResult r = runProcess({"/no/such/binary"}, "", runLimits());
        CHECK(r.status == RunStatus::start_failed && !r.error.empty());
        RunResult m = runProcess({"definitely-not-installed"}, "", runLimits());
        CHECK(m.status == RunStatus::start_failed);
    }

    // --- 12. the whole process group dies on timeout, grandchildren included
    {
        const std::string tree = build(dir, R"(#include <cstdio>
#include <unistd.h>
int main(){ pid_t p = fork(); if (p == 0) { sleep(60); _exit(0); } printf("%d\n", (int)p); fflush(stdout); sleep(60); })", "tree");
        Limits l = runLimits(600);
        l.max_processes = 0;   // this test needs fork to work
        RunResult r = runBinary(tree, "", l, dir.path());
        CHECK(r.status == RunStatus::timed_out);
        const int child = std::atoi(r.stdout_text.c_str());
        CHECK(child > 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::ifstream stat("/proc/" + std::to_string(child) + "/stat");
        std::string line((std::istreambuf_iterator<char>(stat)), {});
        const auto rp = line.rfind(')');
        const bool gone = line.empty() || (rp != std::string::npos && line.size() > rp + 2 && line[rp + 2] == 'Z');
        CHECK(gone);
    }

    // --- 13. compile timeout kills g++ and its children, and returns promptly
    {
        ScratchDir d3(kUid);
        Limits cl = Limits::forCompile(); cl.run_as_uid = kUid; cl.wall_ms = 100;
        auto t = std::chrono::steady_clock::now();
        CompileResult c = compileCpp(wrapUserSource("int main(){}"), d3.path(), "slow", cl);
        CHECK(!c.ok && c.timed_out);
        CHECK(since(t) < 1500);
    }

    // --- 14. peak memory is the program's own, even when this process is large
    {
        std::vector<char> ballast(300u << 20, 1);   // this process now holds ~300 MB
        for (std::size_t i = 0; i < ballast.size(); i += 4096) ballast[i] = static_cast<char>(i);

        const char* tmpl = R"(#include <cstdlib>
#include <unistd.h>
int main(){ size_t n = %zuu << 20; volatile char* p = (volatile char*)malloc(n);
  for (size_t i = 0; i < n; i += 4096) p[i] = 1; usleep(80000); return 0; })";
        auto program = [&](size_t mb, const std::string& name) {
            char src[512]; snprintf(src, sizeof src, tmpl, mb);
            return build(dir, src, name);
        };
        Limits l = runLimits(); l.address_space_bytes = std::size_t(2) << 30;

        RunResult tiny = runBinary(build(dir, "int main(){ return 0; }", "tiny"), "", l, dir.path());
        std::cout << "  tiny program, 300 MB parent: " << tiny.peak_kb << " KB\n";
        CHECK(tiny.status == RunStatus::ok && tiny.peak_kb >= 0 && tiny.peak_kb < 20 * 1024);   // 0 = too short to sample

        RunResult mid = runBinary(program(100, "mid"), "", l, dir.path());      // below the parent's size
        std::cout << "  100 MB program, 300 MB parent: " << mid.peak_kb / 1024 << " MB\n";
        CHECK(mid.peak_kb > 95 * 1024 && mid.peak_kb < 125 * 1024);

        RunResult big = runBinary(program(450, "big"), "", l, dir.path());      // above the parent's size
        std::cout << "  450 MB program, 300 MB parent: " << big.peak_kb / 1024 << " MB\n";
        CHECK(big.peak_kb > 440 * 1024 && big.peak_kb < 480 * 1024);
    }

    // --- 15. many jobs at once (T3 runs a thread pool)
    {
        std::atomic<int> ok{0};
        std::vector<std::thread> ts;
        for (int i = 0; i < 8; ++i)
            ts.emplace_back([&, i] {
                RunResult r = runBinary(sum, std::to_string(i) + " 100\n", runLimits(), dir.path());
                if (r.status == RunStatus::ok && r.stdout_text == std::to_string(i + 100) + "\n") ++ok;
            });
        for (auto& t : ts) t.join();
        CHECK(ok == 8);
    }

    std::cout << (g_fail ? "SANDBOX TESTS FAILED: " + std::to_string(g_fail) : std::string("all sandbox tests passed")) << "\n";
    return g_fail ? 1 : 0;
}
