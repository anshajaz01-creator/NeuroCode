#include "engine/parse/ClangFrontend.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <utility>

#include "sandbox/Compiler.hpp"   // kUserPreamble only (header constant, no link dependency)

namespace nc::parse {

namespace fs = std::filesystem;

std::string toString(CXString s) {
    const char* c = clang_getCString(s);
    std::string r = c ? c : "";
    clang_disposeString(s);
    return r;
}

PresumedLocation presumedLocation(CXSourceLocation loc) {
    CXString file;
    unsigned line = 0, col = 0;
    clang_getPresumedLocation(loc, &file, &line, &col);
    return {toString(file), line, col};
}

std::string wrapForParse(const std::string& user_code) {
    return std::string(kUserPreamble) + "#line 1 \"" + kUserFile + "\"\n" + user_code;
}

namespace {

// ---------------------------------------------------------------- system headers

bool hasBuiltinHeaders(const std::string& dir) {
    std::error_code ec;
    return !dir.empty() && fs::exists(fs::path(dir) / "include" / "stddef.h", ec);
}

std::string runAndTrim(const char* cmd) {
    std::string out;
    if (FILE* p = popen(cmd, "r")) {
        char buf[512];
        while (fgets(buf, sizeof buf, p)) out += buf;
        pclose(p);
    }
    while (!out.empty() && (out.back() == '\n' || out.back() == '\r' || out.back() == ' ')) out.pop_back();
    return out;
}

std::string detectResourceDir() {
    if (const char* env = std::getenv("NC_CLANG_RESOURCE_DIR"))
        if (hasBuiltinHeaders(env)) return env;
#ifdef NC_CLANG_RESOURCE_DIR
    if (hasBuiltinHeaders(NC_CLANG_RESOURCE_DIR)) return NC_CLANG_RESOURCE_DIR;
#endif
    for (const char* cmd : {"clang -print-resource-dir 2>/dev/null", "clang++ -print-resource-dir 2>/dev/null"}) {
        const std::string dir = runAndTrim(cmd);
        if (hasBuiltinHeaders(dir)) return dir;
    }
    return "";
}

const std::string& resourceDir() {
    static const std::string dir = detectResourceDir();   // thread-safe, computed once
    return dir;
}

// Mirrors builtin_includes() in tools/extract_ast.py so training and production see the same headers.
std::vector<std::string> explicitSystemIncludes() {
    std::vector<std::string> inc;
    std::error_code ec;

    std::vector<std::string> gcc;   // /usr/lib/gcc/*/*/include
    for (const auto& triplet : fs::directory_iterator("/usr/lib/gcc", ec))
        for (const auto& version : fs::directory_iterator(triplet.path(), ec)) {
            const fs::path inc_dir = version.path() / "include";
            if (fs::is_directory(inc_dir, ec)) gcc.push_back(inc_dir.string());
        }
    std::sort(gcc.rbegin(), gcc.rend());
    if (!gcc.empty()) inc.push_back("-I" + gcc.front());

    std::vector<std::string> cxx;   // /usr/include/c++/*
    for (const auto& d : fs::directory_iterator("/usr/include/c++", ec)) cxx.push_back(d.path().string());
    std::sort(cxx.rbegin(), cxx.rend());
    if (!cxx.empty()) {
        inc.push_back("-I" + cxx.front());
        std::vector<std::string> arch;
        for (const auto& sub : fs::directory_iterator(cxx.front(), ec)) {
            const std::string name = sub.path().filename().string();
            if (name.size() > 10 && name.compare(name.size() - 10, 10, "-linux-gnu") == 0) arch.push_back(sub.path().string());
        }
        std::sort(arch.begin(), arch.end());
        for (const auto& a : arch) inc.push_back("-I" + a);
    }
    inc.push_back("-I/usr/include");
    return inc;
}

// ---------------------------------------------------------------- parsing

std::vector<Diagnostic> collectDiagnostics(CXTranslationUnit tu) {
    std::vector<Diagnostic> out;
    const unsigned n = clang_getNumDiagnostics(tu);
    for (unsigned i = 0; i < n; ++i) {
        CXDiagnostic d = clang_getDiagnostic(tu, i);
        if (clang_getDiagnosticSeverity(d) >= CXDiagnostic_Error) {
            const PresumedLocation loc = presumedLocation(clang_getDiagnosticLocation(d));
            Diagnostic g;
            g.in_user_code = loc.file == kUserFile;
            g.line = g.in_user_code ? static_cast<int>(loc.line) : 0;
            g.message = toString(clang_getDiagnosticSpelling(d));
            out.push_back(std::move(g));
        }
        clang_disposeDiagnostic(d);
    }
    return out;
}

std::unique_ptr<ParsedUnit> parseOnce(const std::string& source, const ClangOptions& opt, bool explicit_includes) {
    std::vector<std::string> args = {"-std=c++17", "-fsyntax-only"};
    if (opt.resource_dir.empty()) {
        if (!resourceDir().empty()) args.push_back("-resource-dir=" + resourceDir());
    } else {
        args.push_back("-resource-dir=" + opt.resource_dir);
    }
    if (explicit_includes) for (auto& a : explicitSystemIncludes()) args.push_back(std::move(a));
    for (const auto& a : opt.extra_args) args.push_back(a);

    std::vector<const char*> argv;
    for (const auto& a : args) argv.push_back(a.c_str());

    CXIndex index = clang_createIndex(/*excludeDeclarationsFromPCH=*/0, /*displayDiagnostics=*/0);
    CXUnsavedFile buffer{kVirtualFile, source.c_str(), static_cast<unsigned long>(source.size())};
    CXTranslationUnit tu = nullptr;
    const CXErrorCode rc = clang_parseTranslationUnit2(index, kVirtualFile, argv.data(), static_cast<int>(argv.size()),
                                                       &buffer, 1, CXTranslationUnit_None, &tu);
    if (rc != CXError_Success || !tu) {
        if (tu) clang_disposeTranslationUnit(tu);
        clang_disposeIndex(index);
        return nullptr;
    }
    return std::make_unique<ParsedUnit>(index, tu, source, collectDiagnostics(tu));
}

bool missingSystemHeader(const ParsedUnit& u) {
    return std::any_of(u.diagnostics().begin(), u.diagnostics().end(),
                       [](const Diagnostic& d) { return d.message.find("file not found") != std::string::npos; });
}

} // namespace

ParsedUnit::ParsedUnit(CXIndex index, CXTranslationUnit tu, std::string source, std::vector<Diagnostic> diagnostics)
    : index_(index), tu_(tu), source_(std::move(source)), diagnostics_(std::move(diagnostics)) {}

ParsedUnit::~ParsedUnit() {
    if (tu_) clang_disposeTranslationUnit(tu_);
    if (index_) clang_disposeIndex(index_);
}

bool ParsedUnit::hasUserCodeErrors() const {
    return std::any_of(diagnostics_.begin(), diagnostics_.end(), [](const Diagnostic& d) { return d.in_user_code; });
}

std::unique_ptr<ParsedUnit> parseUserCode(const std::string& user_code, const ClangOptions& options) {
    const std::string source = wrapForParse(user_code);

    auto unit = parseOnce(source, options, options.explicit_system_includes);
    // A libclang that cannot find libstdc++ or its builtin headers fails every parse the same way.
    // Retry once with the explicit include list before giving up.
    if (unit && !options.explicit_system_includes && missingSystemHeader(*unit)) {
        if (auto retry = parseOnce(source, options, true); retry && retry->diagnostics().size() < unit->diagnostics().size())
            unit = std::move(retry);
    }
    return unit;
}

} // namespace nc::parse
