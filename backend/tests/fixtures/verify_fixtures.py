#!/usr/bin/env python3
"""Computes feature-vector v1 values from an AST/CFG fixture pair and compares
them with <name>.features.json.

Usage (from backend/tests/fixtures):  python3 -I verify_fixtures.py pair_sum_brute

T1: run your extractor on the same two files and diff against the .features.json.
Only indices that are visible in src/ml/features.md are checked; add the rest
as you confirm them.
"""
import json, re, sys


def walk(node, depth=0):
    """Yield (node, loop_depth) over children, else_children and exprs."""
    yield node, depth
    d = depth + (1 if node.get("type") == "loop" else 0)
    for key in ("children", "else_children", "exprs"):
        for c in node.get(key, []):
            yield from walk(c, d)


def features(ast, cfg):
    fns = [n for n, _ in walk(ast["root"]) if n.get("type") == "function"]
    nodes = [n for n, _ in walk(ast["root"])]
    loops = [(n, d) for n, d in walk(ast["root"]) if n.get("type") == "loop"]
    N = sum(len(f["blocks"]) for f in cfg["functions"])
    E = sum(len(f["edges"]) for f in cfg["functions"])
    P = len(cfg["functions"])
    out_deg = {}
    for f in cfg["functions"]:
        for e in f["edges"]:
            out_deg[(f["name"], e["from"])] = out_deg.get((f["name"], e["from"]), 0) + 1

    def cond(n):
        return (n.get("cond") or "").replace(" ", "")

    idx = {}
    idx[0] = len(loops)                                              # loop_count
    idx[1] = max((d for _, d in loops), default=-1) + 1 if loops else 0   # max_nest_depth
    idx[2] = int(any(f.get("recursive") for f in fns))               # has_recursion
    idx[3] = sum(1 for n in nodes if n.get("type") == "call" and n.get("is_recursive"))
    idx[4] = sum(1 for v in out_deg.values() if v >= 2)              # branch_count (see note)
    idx[5] = N                                                       # cfg_nodes
    idx[6] = E                                                       # cfg_edges
    idx[7] = E - N + 2 * P                                           # cyclomatic
    idx[8] = sum(1 for n, _ in loops if re.search(r"<=?n\b|<=?\w+\.size\(\)", cond(n)))
    idx[9] = sum(1 for n, _ in loops if re.search(r"/2", cond(n)))
    idx[10] = sum(1 for n, _ in loops if re.search(r"=\w+\+1\b", (n.get("init") or "").replace(" ", "")))
    # two_index_pattern: one base array indexed by two different loop variables
    by_base = {}
    for n in nodes:
        if n.get("type") == "array_access":
            by_base.setdefault(n["base"], set()).add(n["index"])
    idx[47] = int(any(len(v) >= 2 for v in by_base.values()))
    return idx


def main(name):
    ast = json.load(open(f"{name}.ast.json"))
    cfg = json.load(open(f"{name}.cfg.json"))
    gold = json.load(open(f"{name}.features.json"))["values"]
    got = features(ast, cfg)
    bad = 0
    for k, v in sorted(got.items()):
        want = gold[str(k)]["value"]
        flag = "ok  " if v == want else "FAIL"
        bad += v != want
        print(f"{flag} idx {k:>2} {gold[str(k)]['name']:<18} got {v}  want {want}")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main(sys.argv[1])
