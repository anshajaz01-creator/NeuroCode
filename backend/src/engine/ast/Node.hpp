#pragma once
#include <optional>
#include <string>
#include <vector>

namespace nc::ast {

// One node of the AST that FeatureExtractor consumes. The shape is FROZEN by
// backend/tools/extract_ast.py (the training-time producer) and backend/tools/features.py
// (the reader): the same field names, the same cursor-kind names, the same rules for when a
// field is present. If this drifts from the Python side the model sees different features in
// production than it trained on, and nothing fails loudly.
//
//   { "type": <clang cursor kind name>, "spelling": str, "dtype": str, "line": int,
//     "op": str, "tokens": str, "has_else": bool, "base_text": str, "index_text": str,
//     "children": [...] }
//
// A generic N-ary tree on purpose: architecture.md section 10 maps the AST to "N-ary tree,
// visitor traversal", and the CFG builder, complexity engine and checks all pattern-match on
// the cursor-kind names below (FOR_STMT, CALL_EXPR, ...) instead of a second private tree.
//
// Optional fields are present only where extract_ast.py writes them:
//   dtype       any node whose type spelling is non-empty
//   tokens      FOR_STMT, WHILE_STMT, DO_STMT, CXX_FOR_RANGE_STMT: first 40 tokens, space-joined
//   op          BINARY_OPERATOR, COMPOUND_ASSIGNMENT_OPERATOR (possibly ""), UNARY_OPERATOR (only
//               when it is one of ++ -- - + ! ~ * &)
//   has_else    IF_STMT (true when it has 3 or more children, exactly as the Python does)
//   base_text, index_text   ARRAY_SUBSCRIPT_EXPR and CALL_EXPR "operator[]" (3 children)
struct Node {
    std::string type;                        // e.g. "FOR_STMT"
    std::string spelling;                    // cursor spelling, "" if none
    int line = 0;                            // 1-based line in the USER's code, 0 if unknown
    std::optional<std::string> dtype;
    std::optional<std::string> tokens;
    std::optional<std::string> op;
    std::optional<bool> has_else;
    std::optional<std::string> base_text;
    std::optional<std::string> index_text;
    std::vector<Node> children;
};

} // namespace nc::ast
