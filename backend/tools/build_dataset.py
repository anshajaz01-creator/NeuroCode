"""
Turn data/manifest.csv into the training dataset: one row per sample with the
feature vector from features.py (N_FEATURES, currently 53).

Reads the split from the manifest (built by build_manifest.py), so the split is
decided in exactly one place: by group, stratified per label.

External samples (CodeContests) are full contest programs. Before feature
extraction their includes, I/O statements and input loops are stripped, so they look like
the hand-written seeds (bare algorithm code). Without this the model can learn
"has cin/cout" instead of the algorithm.

External samples also pass the label sanity filter (LABEL_RULES): e.g. a
`heap_based` sample must declare a priority_queue. Hand-written samples are
trusted and skip it.

Usage (from backend/):
  python3 tools/build_dataset.py                       # writes data/dataset.jsonl
  python3 tools/build_dataset.py --jobs 4 --limit 50   # quick test
"""
import argparse
import csv
import json
import os
import pathlib
import re
import sys
import tempfile
from collections import Counter
from multiprocessing import Pool

sys.path.insert(0, str(pathlib.Path(__file__).parent))
import features as F
from extract_ast import parse_file

# label -> (required_any, forbidden_any), on feature names. Applied to external samples only.
LABEL_RULES = {
    "binary_search":           (["loop_step_halving", "index_mid", "has_recursion",
                                 "lower_bound_calls", "upper_bound_calls"], []),
    "two_pointer":             ([], ["priority_queue_count"]),
    "greedy_scan":             ([], []),
    "sorting_based":           (["sort_calls"], []),
    "dp":                      (["array_access_count", "vector2d_count"], []),
    "graph_traversal":         (["queue_count", "stack_count", "has_recursion", "vector2d_count"], []),
    "hashing":                 (["unordered_set_count", "unordered_map_count", "count_find_member_calls"], []),
    "heap_based":              (["priority_queue_count"], []),
    "linear_search":           ([], ["sort_calls"]),
    "brute_force_pair_search": ([], ["unordered_set_count", "unordered_map_count"]),
    "naive_recursion":         (["has_recursion"], []),
    "sliding_window":          ([], []),
}

# ---- boilerplate stripping ----
# Statement-level, not line-level: contest code often crams a whole program onto
# one or two lines, and dropping whole lines would delete the algorithm with the I/O.
# Each I/O statement becomes an empty statement ';' (so `for(...) cin>>a[i];` stays
# valid), then loops left with an empty body are removed too: input loops are pure
# noise for the feature vector.
STR = r'"(?:\\.|[^"\\])*"'
IO_STMT = re.compile(
    r"(?:\bstd::)?\b(?:cin|cout|cerr)\s*(?:>>|<<)(?:" + STR + r"|[^;\"])*;"
    r"|\b(?:scanf|printf|puts|freopen)\s*\((?:" + STR + r"|[^;\"])*;"
    r"|\b(?:ios_base|ios)::sync_with_stdio\s*\([^)]*\)\s*;"
    r"|\b(?:cin|cout)\.tie\s*\([^)]*\)\s*;"
    r"|\bgetline\s*\([^;]*;"
)
EMPTY_LOOP = re.compile(r"\b(?:for|while)\s*\((?:[^()]|\([^()]*\))*\)\s*;")
INCLUDE_LINE = re.compile(r"^\s*#\s*include")
PREAMBLE = """#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <climits>
#include <cmath>
#include <cstring>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
"""


def strip_io(src: str) -> str:
    """Remove includes, I/O statements, and loops that only did I/O."""
    code = "\n".join(l for l in src.splitlines() if not INCLUDE_LINE.match(l))
    code = IO_STMT.sub(";", code)
    while True:
        new = EMPTY_LOOP.sub(";", code)
        if new == code:
            break
        code = new
    return PREAMBLE + code


def passes_rules(label, vec):
    req, forb = LABEL_RULES.get(label, ([], []))
    if req and not any(vec[F.IDX[n]] > 0 for n in req):
        return False, f"missing any of {req}"
    if forb and any(vec[F.IDX[n]] > 0 for n in forb):
        return False, f"has forbidden {forb}"
    return True, ""


def process(row):
    """Returns (record or None, drop_reason or None)."""
    try:
        code = open(row["path"], errors="ignore").read()
    except OSError:
        return None, "file_missing"
    external = row["source"] != "handwritten"
    if external:
        code = strip_io(code)
    with tempfile.NamedTemporaryFile("w", suffix=".cpp", delete=False) as f:
        f.write(code)
        tmp = f.name
    try:
        ast, errs = parse_file(tmp)
    except Exception:
        return None, "parse_exception"
    finally:
        os.unlink(tmp)
    if errs:
        return None, "parse_errors_after_strip" if external else "parse_errors"
    vec = F.extract(ast)
    if external:
        ok, why = passes_rules(row["label"], vec)
        if not ok:
            return None, f"{row['label']}: {why}"
    return {
        "sample_id": row["sample_id"],
        "label": row["label"],
        "source": row["source"],
        "group_id": row["group_id"],
        "split": row["split"],
        "features": vec,
    }, None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--manifest", default="data/manifest.csv")
    ap.add_argument("--out", default="data/dataset.jsonl")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--limit", type=int, default=0, help="only first N rows, for testing")
    args = ap.parse_args()

    with open(args.manifest) as f:
        rows = list(csv.DictReader(f))
    if args.limit:
        rows = rows[: args.limit]

    kept, drops = [], Counter()
    with Pool(args.jobs) as pool:
        for i, (rec, why) in enumerate(pool.imap(process, rows, chunksize=8), 1):
            if rec:
                kept.append(rec)
            else:
                drops[why] += 1
            if i % 200 == 0:
                print(f"... {i}/{len(rows)} processed, {len(kept)} kept", flush=True)

    with open(args.out, "w") as fh:
        for r in kept:
            fh.write(json.dumps(r) + "\n")

    by = Counter((r["label"], r["split"]) for r in kept)
    labels = sorted({r["label"] for r in kept})
    print(f"\nKept {len(kept)} of {len(rows)} samples, {F.N_FEATURES} features each -> {args.out}\n")
    print(f"{'label':<26}{'train':>8}{'val':>8}{'test':>8}")
    for lab in labels:
        print(f"{lab:<26}" + "".join(f"{by[(lab, s)]:>8}" for s in ("train", "val", "test")))
    if drops:
        print("\nDropped:")
        for k, v in drops.most_common():
            print(f"  {v:>5}  {k}")


if __name__ == "__main__":
    main()