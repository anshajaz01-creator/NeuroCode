#pragma once
#include "engine/ast/Node.hpp"
#include "engine/parse/ClangFrontend.hpp"

namespace nc::parse {

// Same depth cap as tools/extract_ast.py (max_depth=60): children are added only below it.
inline constexpr int kMaxAstDepth = 60;

// libclang translation unit -> the AST JSON shape that tools/extract_ast.py produces
// (see ast/Node.hpp). Root is { "type": "TranslationUnit", "spelling": "user.cpp", "line": 0 } and
// its children are the top-level declarations that come from the USER's code only: the preamble
// (includes, `using namespace std;`) and every system header are left out.
//
// Differences from the Python on purpose, none of which a feature reads:
//   - "line" is the line in the user's code (the Python gives the line in the file it parsed)
//   - the root's spelling is "user.cpp" (the Python writes the file path)
//   - the preamble's `using namespace std;` is not a child of the root
ast::Node buildAst(const ParsedUnit& unit);

} // namespace nc::parse
