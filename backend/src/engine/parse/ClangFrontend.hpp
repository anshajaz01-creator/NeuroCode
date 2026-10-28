#pragma once
#include <memory>
#include <string>
#include <vector>

#include <clang-c/Index.h>

namespace nc::parse {

// The preamble (see sandbox/Compiler.hpp, kUserPreamble) ends with  #line 1 "user.cpp"  so every
// location libclang reports for the user's code carries the user's own line number and the file
// name below. Anything else (preamble lines, headers) is not user code.
inline constexpr const char* kVirtualFile = "nc_input.cpp";  // the buffer handed to libclang
inline constexpr const char* kUserFile = "user.cpp";         // presumed file name after #line

struct Diagnostic {
    int line = 0;               // user line, 0 when the problem is outside the user's code
    bool in_user_code = false;
    std::string message;
};

struct ClangOptions {
    // Directory holding libclang's builtin headers (stddef.h, ...). Empty = autodetect, in order:
    // $NC_CLANG_RESOURCE_DIR, the NC_CLANG_RESOURCE_DIR compile definition, `clang -print-resource-dir`.
    // libclang without these dies on every parse with "'stddef.h' file not found".
    std::string resource_dir;
    // Pass the system GCC/libstdc++ include directories explicitly, the way tools/extract_ast.py
    // does. Also used automatically as a retry when the first parse cannot find a system header.
    bool explicit_system_includes = false;
    std::vector<std::string> extra_args;
};

// Owns the libclang index and translation unit, and the exact buffer that was parsed.
// Offsets inside the translation unit index into source().
class ParsedUnit {
public:
    ParsedUnit(CXIndex index, CXTranslationUnit tu, std::string source, std::vector<Diagnostic> diagnostics);
    ParsedUnit(const ParsedUnit&) = delete;
    ParsedUnit& operator=(const ParsedUnit&) = delete;
    ~ParsedUnit();

    CXTranslationUnit tu() const { return tu_; }
    const std::string& source() const { return source_; }
    const std::vector<Diagnostic>& diagnostics() const { return diagnostics_; }
    bool hasErrors() const { return !diagnostics_.empty(); }    // only errors and fatals are kept
    bool hasUserCodeErrors() const;

private:
    CXIndex index_;
    CXTranslationUnit tu_;
    std::string source_;
    std::vector<Diagnostic> diagnostics_;
};

// Parses user code (a function or a few, no includes needed) as C++17. Never throws for bad code:
// syntax errors come back as diagnostics and the unit still holds whatever libclang recovered.
// Returns nullptr only if libclang itself fails (no translation unit at all).
// Thread safe: every call makes its own CXIndex.
std::unique_ptr<ParsedUnit> parseUserCode(const std::string& user_code, const ClangOptions& options = {});

// The buffer parseUserCode hands to libclang: preamble + #line directive + user code.
std::string wrapForParse(const std::string& user_code);

// libclang helpers shared with AstBuilder.
std::string toString(CXString s);   // converts and disposes
struct PresumedLocation { std::string file; unsigned line = 0; unsigned column = 0; };
PresumedLocation presumedLocation(CXSourceLocation loc);

} // namespace nc::parse
