// AST extraction tests. Plain checks, no framework. Build from backend/:
//   g++ -std=c++20 -I src -I $(llvm-config --includedir) src/engine/parse/*.cpp src/engine/ast/Serializer.cpp
//       tests/test_ast.cpp -L$(llvm-config --libdir) -lclang -Wl,-rpath,$(llvm-config --libdir) -pthread -o test_ast
// Run from backend/ (it reads tests/fixtures/). Tree-for-tree agreement with tools/extract_ast.py is
// checked separately by tests/parity_ast.py.
#include <atomic>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
#include <vector>

#include "engine/ast/Serializer.hpp"
#include "engine/parse/AstBuilder.hpp"
#include "engine/parse/ClangFrontend.hpp"

using nc::ast::Node;

static int g_fail = 0;
#define CHECK(cond)                                                                      \
    do {                                                                                 \
        if (!(cond)) { ++g_fail; std::cerr << "FAIL line " << __LINE__ << ": " #cond "\n"; } \
    } while (0)

static std::string readFile(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

static Node astOf(const std::string& code, const nc::parse::ClangOptions& opt = {}) {
    const auto unit = nc::parse::parseUserCode(code, opt);
    if (!unit) { std::cerr << "no translation unit\n"; ++g_fail; return {}; }
    return nc::parse::buildAst(*unit);
}

static void walk(const Node& n, const std::function<void(const Node&, int)>& f, int depth = 0) {
    f(n, depth);
    for (const auto& c : n.children) walk(c, f, depth + 1);
}

static std::vector<const Node*> find(const Node& root, const std::string& type) {
    std::vector<const Node*> out;
    walk(root, [&](const Node& n, int) { if (n.type == type) out.push_back(&n); });
    return out;
}

int main() {
    const std::string pair_sum = readFile("tests/fixtures/pair_sum_brute.cpp");
    CHECK(!pair_sum.empty());

    // --- 1. root, user-code filtering, user line numbers
    {
        const auto unit = nc::parse::parseUserCode(pair_sum);
        CHECK(unit && !unit->hasErrors());
        const Node root = nc::parse::buildAst(*unit);
        CHECK(root.type == "TranslationUnit" && root.line == 0);
        CHECK(root.children.size() == 1);                       // no preamble, no system headers
        const Node& fn = root.children.at(0);
        CHECK(fn.type == "FUNCTION_DECL" && fn.spelling == "hasPair" && fn.line == 1);
        CHECK(fn.dtype && *fn.dtype == "bool (vector<int> &, int)");
        const auto fors = find(root, "FOR_STMT");
        CHECK(fors.size() == 2 && fors[0]->line == 3 && fors[1]->line == 4);   // the user's lines, not +3
        CHECK(fors[0]->tokens && fors[0]->tokens->rfind("for ( int i = 0 ; i < n ; i ++ )", 0) == 0);
        CHECK(find(root, "IF_STMT").size() == 1 && find(root, "IF_STMT")[0]->line == 5);
        CHECK(find(root, "RETURN_STMT").size() == 2);
    }

    // --- 2. operators, has_else, subscripts
    {
        const Node root = astOf(R"(int f(vector<int>& v, int* p, int n) {
    int raw[10];
    int s = 0;
    s += raw[n];
    s += v[n - 1];
    n++;
    --n;
    s = -s;
    if (s > 0) s = 1; else s = 2;
    if (n) s = 3;
    return s == 1 ? raw[0] : v[n + 1];
})");
        std::vector<std::string> ops;
        for (auto* n : find(root, "BINARY_OPERATOR")) ops.push_back(n->op.value_or("<none>"));
        CHECK(std::find(ops.begin(), ops.end(), "=") != ops.end());
        CHECK(std::find(ops.begin(), ops.end(), "-") != ops.end());
        CHECK(std::find(ops.begin(), ops.end(), "==") != ops.end());
        for (auto* n : find(root, "BINARY_OPERATOR")) CHECK(n->op.has_value());      // present, possibly ""
        const auto comp = find(root, "COMPOUND_ASSIGNMENT_OPERATOR");
        CHECK(comp.size() == 2 && comp[0]->op == "+=");
        std::vector<std::string> unary;
        for (auto* n : find(root, "UNARY_OPERATOR")) unary.push_back(n->op.value_or("<none>"));
        CHECK(std::find(unary.begin(), unary.end(), "++") != unary.end());
        CHECK(std::find(unary.begin(), unary.end(), "--") != unary.end());
        CHECK(std::find(unary.begin(), unary.end(), "-") != unary.end());

        const auto ifs = find(root, "IF_STMT");
        CHECK(ifs.size() == 2 && ifs[0]->has_else == true && ifs[1]->has_else == false);

        const auto raw = find(root, "ARRAY_SUBSCRIPT_EXPR");                   // raw array
        CHECK(!raw.empty() && raw[0]->base_text == "raw" && raw[0]->index_text == "n");
        bool saw_vector_index = false;
        for (auto* n : find(root, "CALL_EXPR"))                                // vector indexing
            if (n->spelling == "operator[]" && n->base_text == "v" && n->index_text == "n - 1") saw_vector_index = true;
        CHECK(saw_vector_index);
        CHECK(find(root, "CONDITIONAL_OPERATOR").size() == 1);
    }

    // --- 3. no includes needed, dtype of containers
    {
        const Node root = astOf("bool f(){ unordered_set<int> s; vector<vector<int>> g; return s.empty() && g.empty(); }");
        bool set_seen = false, vv_seen = false;
        for (auto* n : find(root, "VAR_DECL")) {
            if (n->dtype == "unordered_set<int>") set_seen = true;
            if (n->dtype == "vector<vector<int>>") vv_seen = true;
        }
        CHECK(set_seen && vv_seen);
    }

    // --- 4. syntax errors come back as diagnostics with user line numbers
    {
        const auto unit = nc::parse::parseUserCode("int f() {\n    int x = 1\n    return x;\n}\n");
        CHECK(unit && unit->hasUserCodeErrors());
        bool on_line_2 = false;
        for (const auto& d : unit->diagnostics()) if (d.in_user_code && d.line == 2) on_line_2 = true;
        CHECK(on_line_2);
        CHECK(!nc::parse::buildAst(*unit).children.empty());                   // partial tree still built
        const auto ok_unit = nc::parse::parseUserCode("int f(){ return 1; }");
        CHECK(ok_unit && !ok_unit->hasErrors());
    }

    // --- 5. the "stddef.h not found" trap: bad builtin headers, and the explicit-include path
    {
        const std::string reference = nc::ast::toJsonString(astOf(pair_sum));

        nc::parse::ClangOptions explicit_opt;
        explicit_opt.explicit_system_includes = true;
        CHECK(nc::ast::toJsonString(astOf(pair_sum, explicit_opt)) == reference);   // same tree either way

        nc::parse::ClangOptions broken;
        broken.resource_dir = "/nonexistent/clang/resource";                    // libclang with no builtin headers
        const auto unit = nc::parse::parseUserCode(pair_sum, broken);
        CHECK(unit && !unit->hasErrors());                                      // recovered through the retry
        CHECK(nc::ast::toJsonString(nc::parse::buildAst(*unit)) == reference);
    }

    // --- 6. depth cap matches extract_ast.py (max_depth = 60)
    {
        std::string expr = "1";
        for (int i = 0; i < 90; ++i) expr = "(" + expr + ")";
        const Node root = astOf("int f(){ int x = " + expr + "; return x; }");
        int deepest = 0;
        walk(root, [&](const Node& n, int d) { (void)n; deepest = std::max(deepest, d); });
        CHECK(deepest == nc::parse::kMaxAstDepth + 1);                          // root is depth 0, nodes at depth 60 keep no children
    }

    // --- 7. concurrent parses give identical trees (T3 runs a thread pool)
    {
        const std::string reference = nc::ast::toJsonString(astOf(pair_sum));
        std::atomic<int> same{0};
        std::vector<std::thread> ts;
        for (int i = 0; i < 4; ++i)
            ts.emplace_back([&] { if (nc::ast::toJsonString(astOf(pair_sum)) == reference) ++same; });
        for (auto& t : ts) t.join();
        CHECK(same == 4);
    }

    // --- 8. cost of one parse, for the record
    {
        const auto t0 = std::chrono::steady_clock::now();
        astOf(pair_sum);
        const auto ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
        std::cout << "  one parse + AST build: " << static_cast<int>(ms) << " ms\n";
    }

    std::cout << (g_fail ? "AST TESTS FAILED: " + std::to_string(g_fail) : std::string("all AST tests passed")) << "\n";
    return g_fail ? 1 : 0;
}
