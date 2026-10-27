#!/usr/bin/env python3
"""
Merge the external and hand-written manifests into one, and assign train/val/test
splits BY GROUP (contest problem or seed), stratified per label.

Input : data/manifest_external.csv, data/manifest_seeds.csv
Output: data/manifest.csv   sample_id,label,source,group_id,path,split

Run from backend/:
  python3 tools/build_manifest.py
"""
import argparse, csv, random
from collections import defaultdict, Counter


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--inputs", nargs="+",
                    default=["data/manifest_external.csv", "data/manifest_seeds.csv"])
    ap.add_argument("--out", default="data/manifest.csv")
    ap.add_argument("--val", type=float, default=0.15)
    ap.add_argument("--test", type=float, default=0.15)
    ap.add_argument("--seed", type=int, default=42)
    args = ap.parse_args()
    rng = random.Random(args.seed)

    rows = []
    for path in args.inputs:
        with open(path) as f:
            rows += list(csv.DictReader(f))

    # groups per label (a group never spans two labels)
    groups = defaultdict(set)
    for r in rows:
        groups[r["label"]].add(r["group_id"])

    split_of = {}
    for label, gs in groups.items():
        gs = sorted(gs)
        rng.shuffle(gs)
        n = len(gs)
        n_test = max(1, round(n * args.test)) if n >= 3 else 0
        n_val = max(1, round(n * args.val)) if n >= 3 else 0
        for i, g in enumerate(gs):
            split_of[g] = "test" if i < n_test else "val" if i < n_test + n_val else "train"

    for r in rows:
        r["split"] = split_of[r["group_id"]]

    with open(args.out, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=["sample_id", "label", "source", "group_id", "path", "split"],
                           lineterminator="\n")
        w.writeheader()
        w.writerows(rows)

    # report
    cnt = Counter((r["label"], r["split"]) for r in rows)
    gcnt = Counter((r["label"], split_of[r["group_id"]]) for r in
                   {r["group_id"]: r for r in rows}.values())
    labels = sorted(groups)
    print(f"{'label':<26}{'train':>16}{'val':>16}{'test':>16}")
    print(f"{'':<26}{'samples/groups':>16}{'samples/groups':>16}{'samples/groups':>16}")
    for lab in labels:
        cells = [f"{cnt[(lab, s)]}/{gcnt[(lab, s)]}" for s in ("train", "val", "test")]
        print(f"{lab:<26}" + "".join(f"{c:>16}" for c in cells))
    tot = Counter(r["split"] for r in rows)
    print(f"\nTotal {len(rows)}: train {tot['train']}, val {tot['val']}, test {tot['test']}")
    small = [l for l in labels if len(groups[l]) < 7]
    if small:
        print("Warning: few groups (val/test will be tiny) for:", ", ".join(small))


if __name__ == "__main__":
    main()
