#!/usr/bin/env python3
"""
Import labelled C++ samples from DeepMind CodeContests into NeuroCode's dataset.

Output:
  data/external/<sample_id>.cpp      one file per accepted solution
  data/manifest_external.csv         sample_id,label,source,group_id,path

Run from backend/:
  python3 tools/import_codecontests.py --max-problems 300     # quick trial
  python3 tools/import_codecontests.py                        # full run
"""
import argparse
import csv
import hashlib
import os
import random
import re
import subprocess
import tempfile
from collections import Counter, defaultdict

# Codeforces tag -> NeuroCode label. Edit here if the team changes labels.
TAG_TO_LABEL = {
    "binary search": "binary_search",
    "two pointers": "two_pointer",
    "greedy": "greedy_scan",
    "sortings": "sorting_based",
    "dp": "dp",
    "dfs and similar": "graph_traversal",
    "graphs": "graph_traversal",
}
# Tags that do not change the algorithm much. They are ignored when deciding
# whether a problem has exactly one algorithm tag.
NEUTRAL_TAGS = {"implementation", "*special", "math"}

CPP = 2  # CodeContests language code for C++


def strip_comments(code: str) -> str:
    code = re.sub(r"/\*.*?\*/", "", code, flags=re.S)
    code = re.sub(r"//[^\n]*", "", code)
    return code


def normalized_lines(code: str):
    return [l.rstrip() for l in strip_comments(code).splitlines() if l.strip()]


def problem_label(tags):
    """Return a label if all algorithm tags map to the same single label."""
    tags = [t for t in tags if t not in NEUTRAL_TAGS]
    if not tags:
        return None
    labels = {TAG_TO_LABEL.get(t) for t in tags}
    if len(labels) != 1 or None in labels:
        return None
    return labels.pop()


def compiles(code: str) -> bool:
    with tempfile.NamedTemporaryFile("w", suffix=".cpp", delete=False) as f:
        f.write(code)
        path = f.name
    try:
        r = subprocess.run(["g++", "-std=c++17", "-fsyntax-only", path],
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                           timeout=20)
        return r.returncode == 0
    except subprocess.TimeoutExpired:
        return False
    finally:
        os.unlink(path)


def load_rows(split):
    from datasets import load_dataset  # imported here so --help works without it
    return load_dataset("deepmind/code_contests", split=split, streaming=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--split", default="train")
    ap.add_argument("--out-dir", default="data/external")
    ap.add_argument("--manifest", default="data/manifest_external.csv")
    ap.add_argument("--max-lines", type=int, default=80)
    ap.add_argument("--per-problem", type=int, default=5)
    ap.add_argument("--per-class", type=int, default=300)
    ap.add_argument("--max-problems", type=int, default=0, help="0 = no limit")
    ap.add_argument("--allow-define", action="store_true",
                    help="keep solutions that use #define (off by default)")
    ap.add_argument("--seed", type=int, default=42)
    args = ap.parse_args()

    rng = random.Random(args.seed)
    os.makedirs(args.out_dir, exist_ok=True)

    seen_hashes = set()
    per_class = Counter()
    drop = Counter()
    rows_out = []
    problems_seen = 0

    for row in load_rows(args.split):
        problems_seen += 1
        if args.max_problems and problems_seen > args.max_problems:
            break

        label = problem_label(row.get("cf_tags") or [])
        if label is None:
            drop["tags_not_single_or_unmapped"] += 1
            continue
        if per_class[label] >= args.per_class:
            drop["class_full"] += 1
            continue

        sols = row["solutions"]
        cands = [s for lang, s in zip(sols["language"], sols["solution"]) if lang == CPP]
        if not cands:
            drop["no_cpp_solution"] += 1
            continue
        rng.shuffle(cands)

        group_id = f"cf_{row.get('cf_contest_id', 0)}{row.get('cf_index', '')}" \
            if row.get("cf_contest_id") else "cc_" + row["name"][:40]

        taken = 0
        for code in cands:
            if taken >= args.per_problem or per_class[label] >= args.per_class:
                break
            if not args.allow_define and "#define" in code:
                drop["uses_define"] += 1
                continue
            lines = normalized_lines(code)
            if len(lines) > args.max_lines:
                drop["too_long"] += 1
                continue
            h = hashlib.sha1("\n".join(l.strip() for l in lines).encode()).hexdigest()
            if h in seen_hashes:
                drop["duplicate"] += 1
                continue
            if not compiles(code):
                drop["does_not_compile"] += 1
                continue

            seen_hashes.add(h)
            sample_id = f"cc_{len(rows_out) + 1:05d}"
            path = os.path.join(args.out_dir, sample_id + ".cpp")
            with open(path, "w") as f:
                f.write(code)
            rows_out.append([sample_id, label, "codecontests", group_id, path])
            per_class[label] += 1
            taken += 1

        if problems_seen % 500 == 0:
            print(f"... {problems_seen} problems scanned, {len(rows_out)} samples kept")

    with open(args.manifest, "w", newline="") as f:
        w = csv.writer(f, lineterminator="\n")
        w.writerow(["sample_id", "label", "source", "group_id", "path"])
        w.writerows(rows_out)

    groups = defaultdict(set)
    for r in rows_out:
        groups[r[1]].add(r[3])

    print(f"\nProblems scanned: {problems_seen}")
    print(f"Samples kept:     {len(rows_out)}\n")
    print(f"{'label':<18}{'samples':>8}{'problems':>10}")
    for lab in sorted(set(TAG_TO_LABEL.values())):
        print(f"{lab:<18}{per_class[lab]:>8}{len(groups[lab]):>10}")
    print("\nDropped:")
    for k, v in drop.most_common():
        print(f"  {k:<30}{v}")


if __name__ == "__main__":
    main()