# AST / CFG JSON schema (v1)

Fixture: `pair_sum_brute.cpp` -> `pair_sum_brute.ast.json`, `pair_sum_brute.cfg.json`, `pair_sum_brute.features.json`.
Owner: T4. Consumers: T1 (`FeatureExtractor`), T2 (AST/CFG viewers), T3 (embeds as objects in the job result).

Place the fixtures and `verify_fixtures.py` in `backend/tests/fixtures/`.

`AnalysisResult::ast_json` and `cfg_json` hold these documents as strings. T3 parses them and embeds them as JSON objects in the API response (`result.ast`, `result.cfg`). An empty string means "not produced" and becomes `null`.

## Ground rules

1. Only the user's code appears. Preamble and header cursors are excluded, and `line` is 1-based in the user's code.
2. About 8 node types, not raw Clang kinds. Clang's AST is unstable across versions, so the engine emits only these.
3. Every node has `type` and `line`. Every statement node has `exprs` (list, possibly empty) and, where it nests statements, `children`.
4. `exprs` holds expression-level nodes found directly in that statement (`call`, `array_access`), not in nested statements. To count everything, walk `children`, `else_children` and `exprs`.
5. Text fields (`cond`, `init`, `inc`, `value`, `index`) are the source text with whitespace normalised to single spaces.
6. `schema_version` is checked by `FeatureExtractor`, which must hard-fail on an unknown version.
7. **One source of truth per number.** Anything derived from the CFG (node count, edge count, branch count, cyclomatic) is computed from `cfg_json` only. The AST carries no copy of it.

## AST node types

| type | Fields (besides `type`, `line`, `exprs`) |
|---|---|
| `program` | `children` (functions). Root only, no `line` |
| `function` | `name`, `end_line`, `return_type`, `params[{type,name}]`, `recursive` (bool), `children` |
| `declaration` | `var_name`, `type_name` (element/base type, e.g. `int`), `full_type`, `container` (`vector`, `unordered_set`, `priority_queue`, ... or `null`), `init` (text or `null`) |
| `loop` | `kind` (`for`, `while`, `do_while`, `range_for`), `end_line`, `init`, `cond`, `inc` (each text, `null` if absent), `children` |
| `branch` | `kind` (`if`, `switch`, `ternary`), `end_line`, `cond`, `children` (then part), `else_children` (else part, `[]` if none) |
| `return` | `value` (text or `null`) |
| `assignment` | `target`, `op` (`=`, `+=`, ...), `value` |
| `call` | `callee` (unqualified name, e.g. `sort`), `receiver` (`a` in `a.size()`, `std` for `std::sort`, else `null`), `args` (list of text), `is_recursive` (bool). Appears in `exprs`, or in `children` when it is a statement on its own |
| `array_access` | `base`, `index` (text). Appears in `exprs` |

`else if` is a `branch` nested inside the previous branch's `else_children`.

## CFG

One entry per function in `functions`.

| Field | Meaning |
|---|---|
| `entry`, `exit` | block ids |
| `blocks[].id` | integer, unique within the function |
| `blocks[].kind` | `entry`, `exit`, `basic`, `loop_cond`, `loop_inc`, `branch`, `return` |
| `blocks[].lines` | source lines covered (`[]` for the synthetic exit) |
| `edges[].from`, `to` | block ids |
| `edges[].kind` | `next`, `true`, `false`, `back` (returns to a loop condition), `case`, `default` |

### Construction rules

These rules **are** the definition of `cfg_nodes`, `cfg_edges`, `branch_count` and `cyclomatic`, so T1's Python extractor and the C++ `CfgBuilder` must follow them exactly.

| Construct | Blocks and edges |
|---|---|
| Straight-line statements | Maximal runs share one `basic` block |
| Function | Synthetic `entry` block, one synthetic `exit` block (no lines) |
| `if` / `else if` / `else` | One `branch` block for the condition, `true` and `false` edges, both arms rejoin at the next block |
| `for` | `loop_cond` block (`true` into body, `false` to after), body, `loop_inc` block with a `back` edge to `loop_cond` |
| `while`, `range_for` | `loop_cond` block, body end has a `back` edge to `loop_cond`. No `loop_inc` block |
| `do_while` | Body first, then `loop_cond` with a `back` edge (true) to the body start and `false` to after |
| `switch` | One `branch` block with one `case` edge per case label, a `default` edge (to the default case, or to after if none), `break` goes to after, fall-through goes to the next case |
| ternary `?:` | At statement level, a `branch` block with two arm blocks rejoining |
| `&&`, `\|\|` | Do **not** split blocks |
| `return` | Own `return` block with an edge to `exit` |
| `break` / `continue` | `break` to the block after the loop or switch. `continue` to `loop_inc` for `for`, else to `loop_cond` |
| `goto`, `try`/`catch` | Unsupported in v1: the engine reports `unsupported` instead of building a CFG |

### Derived values

| Quantity | Definition |
|---|---|
| `cfg_nodes` (idx 5) | total blocks over all functions |
| `cfg_edges` (idx 6) | total edges over all functions |
| `branch_count` (idx 4) | blocks with two or more outgoing edges (`loop_cond` and `branch`). **Assumption, T1 to confirm** against "conditional nodes" |
| `cyclomatic` (idx 7) | `edges - nodes + 2` per function, summed over functions (equals `E - N + 2P`). **T1 to confirm** the multi-function case |

Because `switch` adds one edge per case, cyclomatic counts every `case`. The old "decision points + 1" definition counted a switch once. The group has chosen the CFG definition, so use it everywhere.

Fixture values: 11 blocks, 13 edges, 2 back edges, cyclomatic 4, branch_count 3.

## Feature source map (indices visible in `features.md`)

| idx | name | Read from |
|---|---|---|
| 0 | `loop_count` | AST: count of `loop` nodes |
| 1 | `max_nest_depth` | AST: deepest `loop` inside `loop` |
| 2 | `has_recursion` | AST: any `function.recursive` |
| 3 | `recursive_call_count` | AST: `call` nodes with `is_recursive` |
| 4 | `branch_count` | CFG |
| 5, 6 | `cfg_nodes`, `cfg_edges` | CFG |
| 7 | `cyclomatic` | CFG |
| 8 | `loop_bound_n` | AST: `loop.cond` compares to `n` or `.size()` |
| 9 | `loop_bound_half` | AST: `loop.cond` contains `/2` |
| 10 | `loop_from_i_plus_1` | AST: `loop.init` is `x = i + 1` |
| 47 | `two_index_pattern` | AST: `array_access` nodes with the same `base` and two different `index` values |

`tests/fixtures/verify_fixtures.py` computes these from the two JSON files and compares them with `pair_sum_brute.features.json`. T1: run your extractor on the same files and diff.

## Notes for the team

- **T1:** the cyclomatic definition is yours (CFG, index 7), and the AST no longer carries a `cyclomatic` field. Please confirm the two assumptions marked above and the `switch` behaviour.
- **T2:** `cfg` is `{ "schema_version", "functions": [ { name, entry, exit, blocks, edges } ] }`, not the `{ "nodes": [], "edges": [] }` placeholder in api-spec. `ast` is `{ "schema_version", "meta", "root" }`.
- **T3:** embed both as objects, and `null` when the string is empty.
- **Line numbers:** analysis uses a preamble (`#include <bits/stdc++.h>`, `using namespace std;`) with `#line 1`, so lines match the user's editor.