#include "engine/parse/AstBuilder.hpp"

#include <cctype>
#include <string>
#include <vector>

#include "engine/parse/CursorKindNames.hpp"

namespace nc::parse {

namespace {

using ast::Node;

constexpr size_t kMaxTokens = 40;   // MAX_TOKENS in extract_ast.py

std::vector<CXCursor> childrenOf(CXCursor c) {
    std::vector<CXCursor> kids;
    clang_visitChildren(
        c,
        [](CXCursor kid, CXCursor, CXClientData data) {
            static_cast<std::vector<CXCursor>*>(data)->push_back(kid);
            return CXChildVisit_Continue;
        },
        &kids);
    return kids;
}

unsigned expansionOffset(CXSourceLocation loc) {
    unsigned offset = 0;
    clang_getExpansionLocation(loc, nullptr, nullptr, nullptr, &offset);
    return offset;
}

// Tokens of a cursor's extent, in order. cap = 0 means all of them.
struct Token { std::string spelling; unsigned start = 0, end = 0; };
std::vector<Token> tokensOf(CXTranslationUnit tu, CXCursor c, size_t cap) {
    std::vector<Token> out;
    CXToken* toks = nullptr;
    unsigned count = 0;
    clang_tokenize(tu, clang_getCursorExtent(c), &toks, &count);
    for (unsigned i = 0; i < count && (cap == 0 || out.size() < cap); ++i) {
        const CXSourceRange r = clang_getTokenExtent(tu, toks[i]);
        out.push_back({toString(clang_getTokenSpelling(tu, toks[i])),
                       expansionOffset(clang_getRangeStart(r)), expansionOffset(clang_getRangeEnd(r))});
    }
    if (toks) clang_disposeTokens(tu, toks, count);
    return out;
}

// _tokens(): first 40 token spellings joined by one space.
std::string joinedTokens(CXTranslationUnit tu, CXCursor c) {
    std::string s;
    for (const auto& t : tokensOf(tu, c, kMaxTokens)) {
        if (!s.empty()) s += ' ';
        s += t.spelling;
    }
    return s;
}

std::string strip(const std::string& s) {
    size_t b = 0, e = s.size();
    while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
    while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) --e;
    return s.substr(b, e - b);
}

// Python str.split() with no argument: split on runs of whitespace.
std::vector<std::string> splitWhitespace(const std::string& s) {
    std::vector<std::string> out;
    size_t i = 0;
    while (i < s.size()) {
        while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
        size_t j = i;
        while (j < s.size() && !std::isspace(static_cast<unsigned char>(s[j]))) ++j;
        if (j > i) out.push_back(s.substr(i, j - i));
        i = j;
    }
    return out;
}

// _binary_op(): libclang does not expose the operator. It is the first token that lies between the
// end of the left operand and the start of the right one. "" when the cursor is not binary.
std::string binaryOperator(CXTranslationUnit tu, CXCursor c) {
    const auto kids = childrenOf(c);
    if (kids.size() != 2) return "";
    const unsigned lhs_end = expansionOffset(clang_getRangeEnd(clang_getCursorExtent(kids[0])));
    const unsigned rhs_start = expansionOffset(clang_getRangeStart(clang_getCursorExtent(kids[1])));
    for (const auto& t : tokensOf(tu, c, 0))
        if (t.start >= lhs_end && t.end <= rhs_start) return t.spelling;
    return "";
}

// Fallback for a kind value the generated table does not know (a libclang newer than the Python
// bindings it was generated from): CamelCase spelling -> UPPER_SNAKE.
std::string snakeCase(const std::string& camel) {
    std::string out;
    for (size_t i = 0; i < camel.size(); ++i) {
        const unsigned char c = static_cast<unsigned char>(camel[i]);
        if (i > 0 && std::isupper(c)) {
            const bool prev_lower = std::islower(static_cast<unsigned char>(camel[i - 1])) || std::isdigit(static_cast<unsigned char>(camel[i - 1]));
            const bool acronym_end = std::isupper(static_cast<unsigned char>(camel[i - 1])) && i + 1 < camel.size() &&
                                     std::islower(static_cast<unsigned char>(camel[i + 1]));
            if (prev_lower || acronym_end) out += '_';
        }
        out += static_cast<char>(std::toupper(c));
    }
    return out;
}

std::string kindName(CXCursor c) {
    const CXCursorKind kind = clang_getCursorKind(c);
    if (const char* name = cursorKindName(static_cast<int>(kind))) return name;
    return snakeCase(toString(clang_getCursorKindSpelling(kind)));
}

bool isLoop(CXCursorKind k) {
    return k == CXCursor_ForStmt || k == CXCursor_WhileStmt || k == CXCursor_DoStmt || k == CXCursor_CXXForRangeStmt;
}

// to_node() in extract_ast.py, field for field and in the same order of rules.
Node toNode(CXTranslationUnit tu, CXCursor c, int depth) {
    const CXCursorKind kind = clang_getCursorKind(c);
    Node node;
    node.type = kindName(c);
    node.spelling = toString(clang_getCursorSpelling(c));
    node.line = static_cast<int>(presumedLocation(clang_getCursorLocation(c)).line);

    const std::string dtype = toString(clang_getTypeSpelling(clang_getCursorType(c)));
    if (!dtype.empty() && dtype != "NoneType") node.dtype = dtype;

    if (isLoop(kind)) node.tokens = joinedTokens(tu, c);

    if (kind == CXCursor_BinaryOperator || kind == CXCursor_CompoundAssignOperator) {
        node.op = binaryOperator(tu, c);
    }
    if (kind == CXCursor_UnaryOperator) {
        // libclang hides the operator. Read it from the first 40 tokens, prefix or postfix.
        const auto toks = splitWhitespace(joinedTokens(tu, c));
        if (!toks.empty()) {
            static const char* const kPrefix[] = {"++", "--", "-", "+", "!", "~", "*", "&"};
            bool matched = false;
            for (const char* p : kPrefix)
                if (toks.front() == p) { node.op = toks.front(); matched = true; break; }
            if (!matched && (toks.back() == "++" || toks.back() == "--")) node.op = toks.back();
        }
    }
    if (kind == CXCursor_IfStmt) node.has_else = childrenOf(c).size() >= 3;

    if (kind == CXCursor_ArraySubscriptExpr) {
        const auto kids = childrenOf(c);
        if (kids.size() == 2) {
            node.base_text = strip(joinedTokens(tu, kids[0]));
            node.index_text = strip(joinedTokens(tu, kids[1]));
        }
    }
    if (kind == CXCursor_CallExpr && node.spelling == "operator[]") {
        // vector/map indexing is an overloaded operator call. Children: [base, operator ref, index].
        const auto kids = childrenOf(c);
        if (kids.size() == 3) {
            node.base_text = strip(joinedTokens(tu, kids[0]));
            node.index_text = strip(joinedTokens(tu, kids[2]));
        }
    }
    if (kind == CXCursor_CallExpr && node.spelling.empty()) {
        // member calls sometimes have an empty spelling: take the member name
        for (CXCursor kid : childrenOf(c))
            if (clang_getCursorKind(kid) == CXCursor_MemberRefExpr) {
                node.spelling = toString(clang_getCursorSpelling(kid));
                break;
            }
    }

    if (depth < kMaxAstDepth)
        for (CXCursor kid : childrenOf(c)) node.children.push_back(toNode(tu, kid, depth + 1));
    return node;
}

} // namespace

ast::Node buildAst(const ParsedUnit& unit) {
    Node root;
    root.type = "TranslationUnit";
    root.spelling = kUserFile;
    root.line = 0;

    const CXTranslationUnit tu = unit.tu();
    for (CXCursor top : childrenOf(clang_getTranslationUnitCursor(tu))) {
        // Only the user's own declarations: not the preamble, not system headers.
        if (presumedLocation(clang_getCursorLocation(top)).file != kUserFile) continue;
        root.children.push_back(toNode(tu, top, 0));
    }
    return root;
}

} // namespace nc::parse
