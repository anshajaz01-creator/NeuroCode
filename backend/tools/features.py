"""
NeuroCode feature vector, version 2. 53 dimensions.

v2 (before any checkpoint existed) appended 5 pointer-movement features (48-52)
to separate two_pointer, sliding_window and brute_force_pair_search.

FROZEN. The order and the length of FEATURE_NAMES must never change once a
checkpoint exists. feature_mean and feature_std in the model sidecar are tied
to this exact ordering, so a reorder silently corrupts inference.

T4 mirrors this file in C++ as ml/FeatureExtractor.cpp. The week-4 validation
step is: run both on the same 20 files and diff the vectors.
"""

import re

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
    # pointer movement (48-52), added in v2
    "loop_cond_two_vars", "inc_and_dec_in_loop", "running_add_sub",
    "index_minus_var", "inner_while_no_reset",
]

N_FEATURES = len(FEATURE_NAMES)
assert N_FEATURES == 53, f"expected 53 features, got {N_FEATURES}"

IDX = {name: i for i, name in enumerate(FEATURE_NAMES)}


def _walk(node, depth=0):
    yield node, depth
    for ch in node.get("children", []):
        yield from _walk(ch, depth + 1)


def extract(ast_json, cfg_json=None):
    """ast_json: dict from extract_ast.py. Returns a list of N_FEATURES (53) floats."""
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
        elif k == "ARRAY_SUBSCRIPT_EXPR" or (k == "CALL_EXPR" and sp == "operator[]"):
            # raw arrays give ARRAY_SUBSCRIPT_EXPR; vector/map indexing is a call to operator[]
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

    _pointer_features(ast_json, v)
    return v


# ---------------------------------------------------------------- v2 features
LOOPS = {"FOR_STMT", "WHILE_STMT", "DO_STMT", "CXX_FOR_RANGE_STMT"}
COMPARE = {"<", ">", "<=", ">=", "==", "!="}
SUBSCRIPT = ("ARRAY_SUBSCRIPT_EXPR",)


def _unwrap(n):
    """Skip implicit-cast style wrappers down to the real expression."""
    while n.get("type") == "UNEXPOSED_EXPR" and len(n.get("children", [])) == 1:
        n = n["children"][0]
    return n


def _var_name(n):
    n = _unwrap(n)
    return n.get("spelling") if n.get("type") == "DECL_REF_EXPR" else None


def _is_subscript(n):
    return n.get("type") in SUBSCRIPT or (n.get("type") == "CALL_EXPR" and n.get("spelling") == "operator[]")


def _contains_subscript(n):
    return any(_is_subscript(x) for x, _ in _walk(n))


def _modified_vars(n):
    """Variables written to anywhere inside n: x++, --x, x += .., x -= .., x = .."""
    mod = set()
    for x, _ in _walk(n):
        t, op, kids = x.get("type"), x.get("op", ""), x.get("children", [])
        if t == "UNARY_OPERATOR" and op in ("++", "--") and kids:
            name = _var_name(kids[0])
            if name: mod.add(name)
        elif t in ("COMPOUND_ASSIGNMENT_OPERATOR", "BINARY_OPERATOR") and op in ("=", "+=", "-=", "*=", "/=") and kids:
            name = _var_name(kids[0])
            if name: mod.add(name)
    return mod


def _loop_condition(loop):
    """The condition expression of a for/while/do loop, or None."""
    kids = loop.get("children", [])
    t = loop.get("type")
    if t == "WHILE_STMT":
        return kids[0] if kids else None
    if t == "DO_STMT":
        return kids[-1] if kids else None
    if t == "FOR_STMT":
        for k in kids:  # init, cond, inc, body (missing parts are omitted)
            u = _unwrap(k)
            if u.get("type") == "BINARY_OPERATOR" and u.get("op") in COMPARE | {"&&", "||"}:
                return k
    return None


def _pointer_features(root, v):
    two_vars = inc_dec = 0
    adds, subs = set(), set()
    running = 0
    no_reset = 0

    # walk with parent links
    stack = [(root, None, 0)]
    parent = {}
    order = []
    while stack:
        n, p, loops_above = stack.pop()
        parent[id(n)] = p
        order.append((n, loops_above))
        nxt = loops_above + (1 if n.get("type") in LOOPS else 0)
        for c in reversed(n.get("children", [])):
            stack.append((c, n, nxt))

    for n, loops_above in order:
        t, op, kids = n.get("type"), n.get("op", ""), n.get("children", [])

        if t in LOOPS:
            mod = _modified_vars(n)
            cond = _loop_condition(n)
            # 48: condition compares two variables that BOTH move inside the loop (l < r)
            if cond is not None:
                for x, _ in _walk(cond):
                    if x.get("type") == "BINARY_OPERATOR" and x.get("op") in COMPARE and len(x.get("children", [])) == 2:
                        a, b = (_var_name(c) for c in x["children"])
                        if a and b and a != b and a in mod and b in mod:
                            two_vars += 1
                            break
            # 49: one index incremented and a different one decremented in the same loop
            ups, downs = set(), set()
            for x, _ in _walk(n):
                if x.get("type") == "UNARY_OPERATOR" and x.get("children"):
                    name = _var_name(x["children"][0])
                    if name and x.get("op") == "++": ups.add(name)
                    if name and x.get("op") == "--": downs.add(name)
            if ups and downs and (ups - downs) and (downs - ups):
                inc_dec += 1
            # 52: while nested in a loop whose condition variable is not reset just before it
            if t == "WHILE_STMT" and loops_above > 0 and cond is not None:
                cvars = {x.get("spelling") for x, _ in _walk(cond) if x.get("type") == "DECL_REF_EXPR"}
                par = parent.get(id(n))
                reset = False
                if par is not None:
                    for sib in par.get("children", []):
                        if sib is n:
                            break
                        for x, _ in _walk(sib):
                            if x.get("type") == "VAR_DECL" and x.get("spelling") in cvars:
                                reset = True
                if not reset:
                    no_reset += 1

        # 50: running window total: x += a[..] and x -= a[..] on the same x,
        #     or x += a[..] - a[..] in one statement
        if t == "COMPOUND_ASSIGNMENT_OPERATOR" and len(kids) == 2:
            lhs, rhs = _var_name(kids[0]), kids[1]
            if lhs and _contains_subscript(rhs):
                if op == "+=": adds.add(lhs)
                if op == "-=": subs.add(lhs)
                u = _unwrap(rhs)
                if op == "+=" and u.get("type") == "BINARY_OPERATOR" and u.get("op") == "-" \
                        and len(u.get("children", [])) == 2 \
                        and all(_contains_subscript(c) for c in u["children"]):
                    running += 1

        # 51: index minus a variable, e.g. a[i - k] (but not a[i - 1])
        if _is_subscript(n):
            idx = n.get("index_text", "")
            if re.search(r"[A-Za-z_]\w*\s*-\s*[A-Za-z_]\w*", idx):
                v[IDX["index_minus_var"]] += 1

    running += len(adds & subs)
    v[IDX["loop_cond_two_vars"]] = float(two_vars)
    v[IDX["inc_and_dec_in_loop"]] = float(inc_dec)
    v[IDX["running_add_sub"]] = float(running)
    v[IDX["inner_while_no_reset"]] = float(no_reset)


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