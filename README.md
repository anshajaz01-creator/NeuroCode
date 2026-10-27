# NeuroCode

An AI-assisted C++ code reasoning and optimization engine.

A user submits a C++ solution plus a short structured description of the problem it solves. NeuroCode parses the code into an AST, builds a control flow graph, derives its time and space complexity, classifies the algorithm using a trained neural network, runs the code in a sandbox against generated test cases, and, when a better approach exists, produces an optimized version with a measured speedup.

It is not a linter and not a chatbot wrapper. Every layer is built in this repository.

---

## What it does, concretely

**Input**

```cpp
bool solve(vector<int>& a, int k) {
    for (int i = 0; i < a.size(); i++)
        for (int j = i + 1; j < a.size(); j++)
            if (a[i] + a[j] == k) return true;
    return false;
}
```
Problem metadata: input = integer array, n <= 100000, output = boolean, operation = pair sum.

**Output, part 1: analysis**

| Field | Value |
|---|---|
| Detected algorithm | Brute force pair search (0.94) |
| Time complexity | O(n^2) |
| Space complexity | O(1) |
| Verdict | Correct but too slow for n = 100000 |
| Recommended | Hash set lookup, O(n) time / O(n) space |

**Output, part 2: optimized code**

```cpp
bool solve(vector<int>& a, int k) {
    unordered_set<int> seen;
    for (int x : a) {
        if (seen.count(k - x)) return true;
        seen.insert(x);
    }
    return false;
}
```

**Output, part 3: summary of what changed and why**

> **Replaced the inner scan with a hash set lookup.**
>
> The original checks every pair, so the work grows with the square of the input size. The new version stores each value as it passes and asks the set whether the complement `k - x` has already been seen, which answers the same question in one pass.
>
> | | Original | Optimized |
> |---|---|---|
> | Algorithm | Brute force pair search | Hash set lookup |
> | Time | O(n^2) | O(n) expected |
> | Space | O(1) | O(n) |
> | Runtime at n = 50000 | 2841 ms | 8.4 ms |
> | Memory | 412 KB | 2180 KB |
> | Measured speedup | | **338x** |
>
> **Changes made**
> 1. Removed the nested loop over `j` (lines 3 to 5)
> 2. Added an `unordered_set<int> seen` to record values already visited
> 3. Replaced the `a[i] + a[j] == k` test with a complement lookup
>
> **Trade-off:** memory rises from constant to linear in `n`. At the stated bound of n = 100000 this is roughly 400 KB, which is acceptable.
>
> **Verification:** compiled successfully and produced identical output to the original on 200 generated inputs, including empty array, single element, all-equal values, and values near `INT_MAX`.

Every summary is generated from real measurements. Nothing is shown until the optimized code has been compiled and differentially tested against the user's original.

---

## Stack

| Layer | Technology | Reason |
|---|---|---|
| Frontend | React 18 + TypeScript + Vite | Monaco and Recharts are the two components this UI needs most |
| Editor | Monaco Editor | Same editor as VS Code, includes a diff view |
| Styling | Tailwind CSS | Fast, no design system to maintain |
| Backend | C++20 + Drogon | Async HTTP and WebSocket in one framework |
| Parsing | libclang | Real Clang AST, no hand-written parser |
| ML | LibTorch (PyTorch C++ API) | Training happens inside the C++ backend, as required |
| Database | SQLite | Real SQL, zero setup, swappable for Postgres later |
| Sandbox | Forked subprocess with POSIX rlimits | Untrusted user code never runs in the API process |
| Tests | GoogleTest (C++), Vitest (frontend) | Standard |

---

## Repository layout

```
neurocode/
├── README.md
├── docs/
│   ├── architecture.md          system design, contracts, DB schema
│   └── api-spec.md              every endpoint and JSON shape
├── frontend/                    React + TypeScript
└── backend/                     C++20, Drogon, LibTorch
```

Full tree with per-folder ownership is in `docs/architecture.md`.

---

## Team and ownership

Four people, five weeks. Nobody edits outside their own folders.

| Owner | Lane | Folders |
|---|---|---|
| Maheen | ML: features, dataset, LibTorch model, training, inference | `backend/src/ml/`, `backend/data/`, `backend/models/` |
| Mokshi | Frontend: all UI, editor, charts, pages | `frontend/` |
| Wadia | Backend web side: API, WebSocket, auth, DB, job orchestration | `backend/src/api/`, `services/`, `storage/`, `db/` |
| Anshrah | Backend compute side: AST, CFG, complexity, optimizer, sandbox | `backend/src/engine/`, `backend/src/sandbox/` |

The four lanes meet at exactly three files. These are frozen in week 1 and change only by group agreement:

1. `backend/src/engine/IEngine.hpp` (T3 to T4)
2. `backend/src/ml/IPredictor.hpp` (T4 to T1)
3. `docs/api-spec.md` (T3 to T2)

---
## Getting started

### Prerequisites

- CMake 3.20+, a C++20 compiler (GCC 11+ or Clang 14+)
- Drogon 1.9+, SQLite3, nlohmann/json, libsodium, libclang-dev
- LibTorch 2.x (CPU build is fine)
- Node.js 18+

Linux or WSL strongly recommended. LibTorch on native Windows is the single most common setup failure on this project.

### Backend

```bash
cd backend
cmake -B build -DCMAKE_PREFIX_PATH=/path/to/libtorch
cmake --build build -j
sqlite3 data/neurocode.db < db/schema.sql
./build/neurocode        # serves on http://localhost:8080
```

### Frontend

```bash
cd frontend
npm install
npm run dev              # serves on http://localhost:5173
```

### Verify the stack

```bash
curl http://localhost:8080/api/v1/health
```

Expected: `{"status":"ok","db":"ok","model_loaded":true}`

---

## Scope boundaries

Stated up front so the project is judged on what it claims, not on what it does not attempt.

**In scope**
- C++ input only
- Structured problem metadata (a form), not free-text natural language understanding
- A catalog of roughly 15 to 20 classic problem patterns for oracle-based verification
- One trained model: algorithm classification from AST and CFG features
- Template-based code transformation from a fixed optimization catalog
- Static findings from CFG and dataflow analysis (unreachable code, unused variables, suspicious loop bounds, overflow-prone arithmetic)

**Out of scope**
- Natural language problem parsing
- Free-form neural code generation
- Multi-file projects, external libraries beyond the STL
- Proving correctness. Differential testing finds counterexamples; it never proves their absence
- Languages other than C++

**Stretch goals, only if week 3 finishes early**
- Graph neural network over the AST instead of the feature-vector MLP
- A second model for complexity class prediction, cross-checked against the deterministic engine

---

## Honesty policy for results

Three rules the whole team follows when writing the report and the UI:

1. Model outputs are always shown as a ranked list with probabilities, never as a single confident label.
2. A bug is only reported as a bug when a counterexample exists. Anything else is labelled "suspicious pattern".
3. Speedups are measured on real runs, never quoted from complexity classes alone.

---

## Documentation

- [`docs/architecture.md`](docs/architecture.md): layers, module responsibilities, interface contracts, database schema, ML design, DSA mapping, risks
- [`docs/api-spec.md`](docs/api-spec.md): every endpoint, request and response shape, WebSocket protocol, error codes
