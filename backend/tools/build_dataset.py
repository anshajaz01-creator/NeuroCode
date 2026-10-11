"""
Walk a directory of labeled .cpp files, extract features, write dataset.jsonl.

Applies the label sanity filter described in docs: a file labeled `hashing`
that uses no hash container, or one labeled `heap_based` with no priority
queue, is mislabeled and is dropped. This is what makes problem-level labels
usable as algorithm-level labels.

Splits by SEED (the file stem before the first underscore, or the seed file
name), never by sample. Mutations or submissions of the same source must not
appear in both train and test, or the accuracy number is meaningless.

Usage:
  python3 build_dataset.py --src data/seeds     --out data/dataset_seeds.jsonl
  python3 build_dataset.py --src data/prepared  --out data/dataset_codenet.jsonl
"""
import argparse
import hashlib
import json
import pathlib
import random
import sys

sys.path.insert(0, str(pathlib.Path(__file__).parent))
import features as F
from extract_ast import parse_file

# label -> (required_any, forbidden_any) on feature names
LABEL_RULES = {
    "hashing":      (["unordered_set_count", "unordered_map_count", "count_find_member_calls"], []),
    "heap_based":   (["priority_queue_count"], []),
    "bfs":          (["queue_count"], []),
    "dfs":          (["stack_count", "has_recursion"], []),
    "sort_based":   (["sort_calls"], []),
    "dp_2d":        (["vector2d_count"], []),
    "binary_search": (["loop_step_halving", "index_mid", "has_recursion"], []),
    "two_pointer":  ([], ["priority_queue_count"]),
    "prefix_sum":   ([], []),
    "sliding_window": ([], []),
    "dp_1d":        ([], []),
    "greedy_scan":  ([], []),
    "linear_scan":  ([], ["sort_calls"]),
    "brute_force_pair_search": ([], ["unordered_set_count", "unordered_map_count"]),
}


def passes_rules(label, vec):
    req, forb = LABEL_RULES.get(label, ([], []))
    idx = F.IDX
    if req and not any(vec[idx[n]] > 0 for n in req):
        return False, f"missing any of {req}"
    if forb and any(vec[idx[n]] > 0 for n in forb):
        return False, f"has forbidden {forb}"
    return True, ""


def seed_key(path: pathlib.Path):
    """Group mutations and submissions of the same origin together."""
    stem = path.stem
    return stem.split("_m")[0] if "_m" in stem else stem


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--no-filter", action="store_true")
    ap.add_argument("--seed", type=int, default=42)
    args = ap.parse_args()

    src = pathlib.Path(args.src)
    rows, dropped = [], {}

    for f in sorted(src.rglob("*.cpp")):
        label = f.parent.name
        try:
            ast, errs = parse_file(str(f))
        except Exception as e:
            dropped.setdefault("parse_error", 0)
            dropped["parse_error"] += 1
            continue
        vec = F.extract(ast)
        if not args.no_filter:
            ok, why = passes_rules(label, vec)
            if not ok:
                dropped.setdefault(f"{label}: {why}", 0)
                dropped[f"{label}: {why}"] += 1
                continue
        rows.append({
            "file": str(f),
            "label": label,
            "seed": f"{label}/{seed_key(f)}",
            "features": vec,
        })

    # split by seed, deterministic
    seeds = sorted({r["seed"] for r in rows})
    rnd = random.Random(args.seed)
    rnd.shuffle(seeds)
    n = len(seeds)
    tr = set(seeds[: int(n * 0.70)])
    va = set(seeds[int(n * 0.70): int(n * 0.85)])
    for r in rows:
        r["split"] = "train" if r["seed"] in tr else ("val" if r["seed"] in va else "test")

    with open(args.out, "w") as fh:
        for r in rows:
            fh.write(json.dumps(r) + "\n")

    by_label = {}
    for r in rows:
        by_label.setdefault(r["label"], 0)
        by_label[r["label"]] += 1
    print(f"kept {len(rows)} samples across {len(by_label)} labels, {n} seeds")
    for k in sorted(by_label):
        print(f"  {k:26s} {by_label[k]}")
    if dropped:
        print("\ndropped:")
        for k, v in sorted(dropped.items()):
            print(f"  {k}: {v}")
    counts = {s: sum(1 for r in rows if r["split"] == s) for s in ("train", "val", "test")}
    print(f"\nsplit: {counts}")


if __name__ == "__main__":
    main()
