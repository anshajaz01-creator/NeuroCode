#include "sandbox/Compiler.hpp"

#include <fstream>
#include <regex>
#include <unistd.h>

#include "sandbox/Runner.hpp"

namespace nc {

std::string wrapUserSource(const std::string& user_code) {
    return std::string(kUserPreamble) + "#line 1 \"user.cpp\"\n" + user_code;
}

std::string summarizeCompileError(const std::string& out) {
    static const std::regex kError(R"(([^\s:]+):(\d+):(?:\d+:)?\s*(?:fatal )?error:\s*(.*))");
    std::smatch m;
    if (std::regex_search(out, m, kError)) return "line " + m[2].str() + ": " + m[3].str();

    // Linker errors and the like carry no line number: use the first non-empty line.
    std::size_t pos = 0;
    while (pos < out.size()) {
        std::size_t end = out.find('\n', pos);
        if (end == std::string::npos) end = out.size();
        std::string line = out.substr(pos, end - pos);
        if (line.find_first_not_of(" \t\r") != std::string::npos) return line;
        pos = end + 1;
    }
    return "compilation failed";
}

CompileResult compileCpp(const std::string& source, const std::string& work_dir,
                         const std::string& name, const Limits& limits) {
    CompileResult r;
    const std::string src_path = work_dir + "/" + name + ".cpp";
    const std::string bin_path = work_dir + "/" + name;

    {
        std::ofstream f(src_path, std::ios::binary);
        f << source;
        if (!f) {
            r.sandbox_error = true;
            r.error_summary = "could not write " + name + ".cpp";
            r.error_full = r.error_summary;
            return r;
        }
    }
    if (limits.run_as_uid >= 0 && geteuid() == 0 && chown(src_path.c_str(), static_cast<uid_t>(limits.run_as_uid), static_cast<gid_t>(limits.run_as_uid)) != 0) {
        r.sandbox_error = true;
        r.error_summary = "could not hand the source to the sandbox user";
        r.error_full = r.error_summary;
        return r;
    }

    const std::vector<std::string> argv = {
        "g++", "-std=c++17", "-O2", "-pipe", "-x", "c++",
        "-fdiagnostics-color=never", "-fmax-errors=5",
        src_path, "-o", bin_path};
    const std::vector<std::string> env = {"PATH=/usr/local/bin:/usr/bin:/bin", "TMPDIR=" + work_dir, "LANG=C"};

    const RunResult run = runProcess(argv, "", limits, work_dir, env);

    if (run.status == RunStatus::start_failed) {
        r.sandbox_error = true;
        r.error_summary = run.error;
        r.error_full = run.error;
        return r;
    }
    if (run.status == RunStatus::timed_out) {
        r.timed_out = true;
        r.error_summary = "compilation exceeded " + std::to_string(limits.wall_ms) + " ms";
        r.error_full = r.error_summary;
        return r;
    }

    std::string text = run.stderr_text.empty() ? run.stdout_text : run.stderr_text;
    // Keep scratch paths out of messages shown to users.
    for (std::size_t p; (p = text.find(work_dir + "/")) != std::string::npos;)
        text.erase(p, work_dir.size() + 1);

    if (run.status != RunStatus::ok) {
        r.error_full = text;
        r.error_summary = summarizeCompileError(text);
        return r;
    }
    r.ok = true;
    r.binary_path = bin_path;
    return r;
}

} // namespace nc
