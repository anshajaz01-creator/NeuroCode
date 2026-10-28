// Prints the AST JSON for a C++ file, in the shape tools/extract_ast.py produces.
//   nc_extract file.cpp                 AST JSON on stdout
//   nc_extract --print-wrapped file.cpp the exact text handed to libclang (preamble + #line + code)
//   nc_extract --strict file.cpp        exit 1 if libclang reports errors
// Diagnostics go to stderr. Used by tests/parity_ast.py to compare against the Python extractor.
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "engine/ast/Serializer.hpp"
#include "engine/parse/AstBuilder.hpp"
#include "engine/parse/ClangFrontend.hpp"

int main(int argc, char** argv) {
    bool strict = false, print_wrapped = false;
    std::string path;
    for (int i = 1; i < argc; ++i) {
        const std::string a = argv[i];
        if (a == "--strict") strict = true;
        else if (a == "--print-wrapped") print_wrapped = true;
        else path = a;
    }
    if (path.empty()) { std::cerr << "usage: nc_extract [--strict] [--print-wrapped] file.cpp\n"; return 2; }

    std::ifstream in(path, std::ios::binary);
    if (!in) { std::cerr << "cannot read " << path << "\n"; return 2; }
    const std::string code((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    if (print_wrapped) { std::cout << nc::parse::wrapForParse(code); return 0; }

    const auto unit = nc::parse::parseUserCode(code);
    if (!unit) { std::cerr << "libclang could not create a translation unit\n"; return 3; }
    for (const auto& d : unit->diagnostics())
        std::cerr << (d.in_user_code ? "line " + std::to_string(d.line) : std::string("preamble")) << ": " << d.message << "\n";
    if (strict && unit->hasErrors()) return 1;

    std::cout << nc::ast::toJsonString(nc::parse::buildAst(*unit)) << "\n";
    return 0;
}
