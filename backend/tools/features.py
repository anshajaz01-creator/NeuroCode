"""
NeuroCode feature vector, version 1. 48 dimensions.

FROZEN. The order and the length of FEATURE_NAMES must never change once a
checkpoint exists. feature_mean and feature_std in the model sidecar are tied
to this exact ordering, so a reorder silently corrupts inference.

T4 mirrors this file in C++ as ml/FeatureExtractor.cpp. The week-4 validation
step is: run both on the same 20 files and diff the vectors.
"""

FEATURE_NAMES = [
    # loop shape (0-9)
    "loop_count", "for_count", "while_count", "rangefor_count",
    "max_nest_depth", "loop_bound_size_call", "loop_bound_var",
    "loop_from_i_plus_1", "loop_step_halving", "loop_step_doubling",
    # recursion (10-13)
    "has_recursion", "recursive_fn_count", "self_call_count", "fn_count",
    # control flow (14-20)
    "if_count", "else_count", "ternary_count", "switch_count",
    "break_count", "continue_count", "cyclomatic",
    # containers (21-31)
    "vector_count", "vector2d_count", "set_count", "unordered_set_count",
    "map_count", "unordered_map_count", "queue_count", "stack_count",
    "priority_queue_count", "string_count", "pair_count",
    # stl calls (32-38)
    "sort_calls", "lower_bound_calls", "upper_bound_calls", "find_calls",
    "max_element_calls", "push_pop_calls", "count_find_member_calls",
    # index and access patterns (39-44)
    "array_access_count", "index_i", "index_i_plus_1", "index_i_minus_1",
    "index_mid", "two_index_same_array",
    # arithmetic and comparison mix (45-47)
    "add_sub_count", "mul_div_count", "compare_count",
]

N_FEATURES = len(FEATURE_NAMES)
assert N_FEATURES == 48, f"expected 48 features, got {N_FEATURES}"

IDX = {name: i for i, name in enumerate(FEATURE_NAMES)}


def _walk(node, depth=0):
    yield node, depth
    for ch in node.get("children", []):
        yield from _walk(ch, depth + 1)


def extract(ast_json, cfg_json=None):
    """ast_json: dict from extract_ast.py. Returns a list of 48 floats."""
    v = [0.0] * N_FEATURES

    def bump(name, amount=1.0):
        v[IDX[name]] += amount

    loop_kinds = {"FOR_STMT", "WHILE_STMT", "DO_STMT", "CXX_FOR_RANGE_STMT"}
    max_loop_depth = 0
    loop_depth_stack = []
    array_names_by_index = {}

    for node, depth in _walk(ast_json):
        k = node.get("type", "")
        sp = node.get("spelling", "") or ""
        tp = node.get("dtype", "") or ""
        tok = node.get("tokens", "") or ""

        if k in loop_kinds:
            bump("loop_count")
            if k == "FOR_STMT":
                bump("for_count")
            elif k in ("WHILE_STMT", "DO_STMT"):
                bump("while_count")
            else:
                bump("rangefor_count")
            nest = sum(1 for _, d in [(node, depth)]) + _loop_ancestors(ast_json, node)
            max_loop_depth = max(max_loop_depth, nest)
            flat = tok.replace(" ", "")
            if ".size()" in flat or "size_t" in flat:
                bump("loop_bound_size_call")
            if "+1" in flat:
                bump("loop_from_i_plus_1")
            if "/2" in flat or ">>1" in flat:
                bump("loop_step_halving")
            if "*2" in flat or "<<1" in flat:
                bump("loop_step_doubling")

        elif k == "IF_STMT":
            bump("if_count")
            if node.get("has_else"):
                bump("else_count")
        elif k == "CONDITIONAL_OPERATOR":
            bump("ternary_count")
        elif k == "SWITCH_STMT":
            bump("switch_count")
        elif k == "BREAK_STMT":
            bump("break_count")
        elif k == "CONTINUE_STMT":
            bump("continue_count")
        elif k == "FUNCTION_DECL":
            bump("fn_count")
        elif k == "ARRAY_SUBSCRIPT_EXPR":
            bump("array_access_count")
            idx = node.get("index_text", "")
            base = node.get("base_text", "")
            if idx in ("i", "idx", "p"):
                bump("index_i")
            if "+ 1" in idx or "+1" in idx:
                bump("index_i_plus_1")
            if "- 1" in idx or "-1" in idx:
                bump("index_i_minus_1")
            if "mid" in idx or "middle" in idx:
                bump("index_mid")
            array_names_by_index.setdefault(base, set()).add(idx)
        elif k == "CALL_EXPR":
            n = sp
            if n == "sort":
                bump("sort_calls")
            elif n == "lower_bound":
                bump("lower_bound_calls")
            elif n == "upper_bound":
                bump("upper_bound_calls")
            elif n == "find":
                bump("find_calls")
            elif n in ("max_element", "min_element"):
                bump("max_element_calls")
            elif n in ("push", "pop", "push_back", "pop_back", "push_front", "emplace"):
                bump("push_pop_calls")
            elif n in ("count", "contains"):
                bump("count_find_member_calls")
        elif k == "BINARY_OPERATOR":
            op = node.get("op", "")
            if op in ("+", "-", "+=", "-="):
                bump("add_sub_count")
            elif op in ("*", "/", "%", "*=", "/="):
                bump("mul_div_count")
            elif op in ("<", ">", "<=", ">=", "==", "!="):
                bump("compare_count")

        # container types, counted on DECLARATIONS only.
        # Counting every expression node inflates these by 4-5x.
        if tp and k in ("VAR_DECL", "PARM_DECL", "FIELD_DECL"):
            t = tp.replace(" ", "")
            if "vector<vector<" in t:
                bump("vector2d_count")
            elif "vector<" in t:
                bump("vector_count")
            if "unordered_set<" in t:
                bump("unordered_set_count")
            elif "set<" in t:
                bump("set_count")
            if "unordered_map<" in t:
                bump("unordered_map_count")
            elif "map<" in t:
                bump("map_count")
            if "priority_queue<" in t:
                bump("priority_queue_count")
            elif "queue<" in t:
                bump("queue_count")
            if "stack<" in t:
                bump("stack_count")
            if "string" in t:
                bump("string_count")
            if "pair<" in t:
                bump("pair_count")

    v[IDX["max_nest_depth"]] = float(max_loop_depth)
    v[IDX["loop_bound_var"]] = v[IDX["loop_count"]] - v[IDX["loop_bound_size_call"]]

    # recursion: a function that calls its own name
    fns = {n.get("spelling") for n, _ in _walk(ast_json) if n.get("type") == "FUNCTION_DECL"}
    calls = [n.get("spelling") for n, _ in _walk(ast_json) if n.get("type") == "CALL_EXPR"]
    rec = fns.intersection(calls)
    v[IDX["has_recursion"]] = 1.0 if rec else 0.0
    v[IDX["recursive_fn_count"]] = float(len(rec))
    v[IDX["self_call_count"]] = float(sum(1 for c in calls if c in rec))

    # two different indices into the same array (i and j pattern)
    v[IDX["two_index_same_array"]] = float(
        sum(1 for _, idxs in array_names_by_index.items() if len(idxs) >= 2)
    )

    # cyclomatic complexity, decision-point definition.
    # T4's CFG version must use the SAME definition or the vectors diverge.
    v[IDX["cyclomatic"]] = (
        v[IDX["if_count"]] + v[IDX["loop_count"]] + v[IDX["ternary_count"]]
        + v[IDX["switch_count"]] + 1.0
    )

    return v


def _loop_ancestors(root, target):
    """Depth of loop nesting above target. Recomputed by path search, fine for
    the small trees we deal with."""
    loop_kinds = {"FOR_STMT", "WHILE_STMT", "DO_STMT", "CXX_FOR_RANGE_STMT"}

    def dfs(node, loops):
        if node is target:
            return loops
        nxt = loops + (1 if node.get("type") in loop_kinds else 0)
        for ch in node.get("children", []):
            r = dfs(ch, nxt)
            if r is not None:
                return r
        return None

    r = dfs(root, 0)
    return r if r is not None else 0


if __name__ == "__main__":
    import json, sys
    ast = json.load(open(sys.argv[1]))
    vec = extract(ast)
    for name, val in zip(FEATURE_NAMES, vec):
        if val:
            print(f"{name:26s} {val}")
