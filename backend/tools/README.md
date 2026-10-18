# ML data tools

Everything here runs offline on your laptop. Nothing in the C++ backend makes a
network call or shells out to Python. These scripts only produce files the
backend later reads.

## Setup

    python3 -m venv ~/venvs/neurocode
    source ~/venvs/neurocode/bin/activate
    pip install -r tools/requirements.txt

`extract_ast.py` points libclang at the system GCC headers, because the pip
wheel ships no builtin headers and every parse fails with "stddef.h not found".
If your GCC version differs, check `builtin_includes()`.

## Pipeline

Run from `backend/`, in this order:

    python3 tools/import_codecontests.py --max-problems 1500   # external samples (needs internet)
    python3 tools/mutate_seeds.py                              # seeds -> ~20 variants each
    python3 tools/build_manifest.py                            # merge + split by group
    python3 tools/build_dataset.py                             # features -> data/dataset.jsonl
    python3 tools/baseline_check.py                            # sanity check the features

| File | Job | Output |
|---|---|---|
| `import_codecontests.py` | CodeContests problems with a single algorithm tag -> C++ solutions | `data/external/`, `data/manifest_external.csv` |
| `mutate_seeds.py` | Hand-written seeds -> label-preserving variants (rename, for->while, increment, dead code) | `data/mutated/`, `data/manifest_seeds.csv` |
| `build_manifest.py` | Merge manifests, assign train/val/test by group, stratified per label | `data/manifest.csv` |
| `extract_ast.py` | libclang -> AST JSON, the schema shared with T4's engine | (library) |
| `features.py` | AST JSON -> 53 floats (v2, frozen). Reference impl, mirrored in C++ | (library) |
| `build_dataset.py` | Manifest -> stripped code -> AST -> features, label filter on external | `data/dataset.jsonl` |
| `baseline_check.py` | Linear classifier + grouped 5-fold CV on the features. Not the project model | report |

## Labels

12 classes, defined in `src/ml/labels.json` (alphabetical). Folder names under
`data/seeds/` and the optimizer catalog must use the same strings.

| Source | Labels |
|---|---|
| CodeContests | binary_search, two_pointer, greedy_scan, sorting_based, dp, graph_traversal |
| Hand-written seeds | brute_force_pair_search, linear_search, naive_recursion, sliding_window, heap_based, hashing (+ top-ups for binary_search, two_pointer, sorting_based) |

## Splits

Decided once, in `build_manifest.py`: by group (contest problem or seed), so no
problem or seed appears in two splits. Mutations of the same seed always share a
split. `build_dataset.py` copies the split, it never re-splits.

## Why external code is stripped

Contest solutions are full programs with `main`, `cin`, `cout` and input loops.
Seeds are bare algorithm functions. If the boilerplate stayed, the model could
learn "has I/O" instead of the algorithm. `build_dataset.py` removes includes and
I/O statements, then any loop left with an empty body. It works per statement,
not per line, because contest code often crams a program onto one line.

## Why the label filter exists

A problem tag is not an algorithm label: a problem tagged `binary search` can
have solutions that never binary-search. `build_dataset.py` applies per-label
rules to external samples (e.g. `sorting_based` must call `sort`,
`binary_search` must show halving, a `mid` index, recursion or `lower_bound`)
and drops anything that fails. Hand-written samples are trusted and skip it.

## Features (v2, frozen)

53 features. 0-47 are v1 (loops, recursion, control flow, containers, STL calls,
index patterns, arithmetic). 48-52 were added in v2 to separate the pointer
algorithms:

| # | Feature | Fires on |
|---|---|---|
| 48 | `loop_cond_two_vars` | loop condition compares two variables that both change in the loop (`l < r`) |
| 49 | `inc_and_dec_in_loop` | one index `++` and a different one `--` in the same loop |
| 50 | `running_add_sub` | `x += a[..]` and `x -= a[..]` on the same x, or `x += a[..] - a[..]` |
| 51 | `index_minus_var` | index minus a variable, `a[i - k]` (not `a[i - 1]`) |
| 52 | `inner_while_no_reset` | a `while` inside a loop whose condition variable is not re-declared just before it |

Order and length are now frozen. Any change means retraining and updating the
C++ mirror, `kFeatureDim` in StubPredictor, and the model checkpoint.

## Known limits

- Some features read variable names (`index_i`: i/idx/p, `index_mid`: mid).
  The mutation rename pool excludes these names so it never fakes them.
- Loop features read the first 40 tokens of a loop, which include the start of
  any nested loop, so an outer loop can pick up `loop_from_i_plus_1` from its
  inner loop. Consistent across samples, so harmless, but the C++ mirror must
  behave the same.
- `cyclomatic` uses the decision-point definition; T4's CFG must use the same.
- Vector and map indexing (`a[i]` on a vector) is a call to `operator[]` in the
  AST, not an ARRAY_SUBSCRIPT_EXPR. Both count as array access.