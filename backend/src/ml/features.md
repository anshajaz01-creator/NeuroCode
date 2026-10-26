# Feature vector, version 1

48 dimensions. Order and length are FROZEN. Index 7 is cyclomatic complexity
forever. Changing either after a checkpoint exists silently breaks inference,
because feature_mean and feature_std in the model sidecar are tied to this order.

| idx | name                 | source | notes                       |
| --- | -------------------- | ------ | --------------------------- |
| 0   | loop_count           | AST    | for, while, range-for       |
| 1   | max_nest_depth       | AST    | deepest loop nesting        |
| 2   | has_recursion        | AST    | 0 or 1                      |
| 3   | recursive_call_count | AST    |                             |
| 4   | branch_count         | CFG    | conditional nodes           |
| 5   | cfg_nodes            | CFG    |                             |
| 6   | cfg_edges            | CFG    |                             |
| 7   | cyclomatic           | CFG    | edges - nodes + 2           |
| 8   | loop_bound_n         | AST    | count of loops bounded by n |
| 9   | loop_bound_half      | AST    | count bounded by n/2 or i/2 |
| 10  | loop_from_i_plus_1   | AST    | triangular inner loop       |

...
| 47 | two_index_pattern | AST | i and j index the same array |
