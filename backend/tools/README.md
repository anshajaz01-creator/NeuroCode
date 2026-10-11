# ML data tools

Everything here runs offline on your laptop. Nothing in the C++ backend
makes a network call or shells out to Python.

## Setup

    pip install libclang --break-system-packages

`extract_ast.py` points libclang at the system GCC headers, because the pip
wheel ships no builtin headers and every parse fails with "stddef.h not found".
If your GCC version differs, check `builtin_includes()`.

## Files

| File | Job |
|---|---|
| `extract_ast.py` | libclang → AST JSON, the schema shared with T4's engine |
| `features.py` | AST JSON → 48 floats. Reference impl, mirrored in C++ by T4 |
| `codenet_prepare.py` | CodeNet submissions → clean labeled .cpp snippets |
| `build_dataset.py` | labeled .cpp tree → dataset.jsonl with seed-level splits |
| `mutate.py` | seeds → label-preserving variants (week 2) |

## Seeds

    python3 tools/build_dataset.py --src data/seeds --out data/dataset_seeds.jsonl --no-filter

`--no-filter` because seeds are hand-written and trusted. The label rules exist
to clean noisy CodeNet data, not to second-guess your own files.

## CodeNet

1. Download Project CodeNet (Apache 2.0). The C++1000 benchmark is enough;
   the full 14M-sample dataset is not needed.
2. Read problem statements and fill `data/problem_map.json`. Budget five
   problems per label, so about 70 statements to read.
3. Prepare:

        python3 tools/codenet_prepare.py --root /path/to/Project_CodeNet_C++1000 \
            --layout benchmark --map data/problem_map.json \
            --out data/prepared --limit 200

   Use `--layout full` for the complete dataset, which has metadata CSVs and
   lets the script keep only submissions with status Accepted.

4. Build:

        python3 tools/build_dataset.py --src data/prepared --out data/dataset_codenet.jsonl

## Why the label filter exists

A CodeNet problem label is not an algorithm label. Five hundred submissions to
one "pair with given sum" problem contain brute force, hashing, and
sort-then-two-pointer solutions. Labeling them all `hashing` poisons roughly
40% of that class.

`build_dataset.py` applies per-label rules (a `hashing` sample must use a hash
container, a `heap_based` sample must use a priority queue) and drops anything
that fails. Expect to lose 40-60% of submissions. That is the filter working.

Once T4's complexity engine exists, add a second gate: derived complexity must
match `expected_time` in `problem_map.json`.

## Known limits

- Boilerplate stripping is line-based and crude. The compile gate catches the
  failures, but some legitimate submissions are lost.
- `#define int long long` survives stripping, so type features read `long long`
  across those files. Not fatal, just expect the distribution to look odd.
- CFG features are currently AST-derived approximations. `cyclomatic` uses the
  decision-point definition; T4's real CFG must use the same one or the two
  feature extractors diverge.
