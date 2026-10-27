# NeuroCode Architecture

Version 1.0. Frozen at the end of week 1. Changes require group agreement.

---

## 1. Design principles

1. **Layers talk downward only.** Controllers never touch SQLite. The engine never knows HTTP exists. The ML module never opens a database.
2. **Deterministic analysis is the foundation, ML is the advisor.** Nothing is reported as fact on the strength of a model prediction alone.
3. **Every module ships a stub on day one.** T4's engine returns fake results in week 1 so T3 can build the API. T1's predictor returns a random label so T4 can wire inference before the model exists.
4. **Three interface files hold the system together.** They are defined in section 5 and frozen.

---

## 2. System overview

```
┌──────────────────────── REACT + TYPESCRIPT (T2) ─────────────────────────┐
│  Monaco editor │ Problem form │ Analysis panel │ Diff view │ Live charts │
└──────────────┬───────────────────────────────────────▲───────────────────┘
       REST (commands)                          WebSocket (progress)
┌──────────────▼───────────────────────────────────────┴───────────────────┐
│  API LAYER (T3)  Drogon controllers                                      │
│  routing, JSON in/out, token auth, validation, CORS                      │
├──────────────────────────────────────────────────────────────────────────┤
│  SERVICE LAYER (T3)                                                      │
│  JobManager (queue + thread pool) │ ProgressBroadcaster │ AuthService    │
├───────────────────────┬──────────────────────┬───────────────────────────┤
│  ANALYSIS ENGINE (T4) │  ML MODULE (T1)      │  SANDBOX (T4)             │
│  libclang AST         │  feature extraction  │  compile + run user code  │
│  CFG builder          │  LibTorch MLP        │  time / memory limits     │
│  complexity engine    │  trainer + predictor │  differential testing     │
│  optimizer catalog    │                      │                           │
├───────────────────────┴──────────────────────┴───────────────────────────┤
│  STORAGE LAYER (T3)  repositories → SQLite   +   files on disk           │
└──────────────────────────────────────────────────────────────────────────┘
```

---

## 3. Request flow: analyze

```
React: POST /api/v1/jobs {type:"analyze", code, problem}
  │
  ▼
JobController validates, JobRepo inserts row (status=queued), returns job_id
  │
  ▼
JobManager pushes onto queue, ThreadPool worker picks it up
  │
  ▼
Engine::analyze(code, problem, on_progress)
  │
  ├─ 1. libclang → Clang AST                          10%
  ├─ 2. ASTBuilder → internal simplified AST          20%
  ├─ 3. CFGBuilder → control flow graph               30%
  ├─ 4. ComplexityEngine → O(time), O(space)          45%
  ├─ 5. FeatureExtractor (ML) → float vector          55%
  ├─ 6. Predictor (ML) → ranked algorithm labels      65%
  ├─ 7. StaticChecks over CFG → findings              75%
  ├─ 8. TestGenerator + Sandbox + Oracle              90%
  │       user output vs reference output → counterexamples
  └─ 9. Optimizer → candidate transformation          100%
  │
  ▼  (every step calls on_progress, which pushes over WebSocket)
JobRepo updates row (status=done, result JSON)
  │
  ▼
React polls GET /api/v1/jobs/{id} or receives "done" on the socket
```

Optimization is a separate job type that reuses steps 1 to 7 and then generates and verifies code.

---

## 4. File structure with ownership

```
neurocode/
├── README.md                                   [ALL]
├── docs/
│   ├── architecture.md                         [ALL]
│   ├── api-spec.md                             [T3 writes, ALL approve]
│   └── report/                                 [ALL, week 5]
│
├── frontend/                        ══════ T2 OWNS EVERYTHING ══════
│   ├── package.json
│   ├── vite.config.ts
│   ├── tailwind.config.js
│   └── src/
│       ├── main.tsx
│       ├── App.tsx
│       ├── api/
│       │   ├── client.ts                REST wrapper, attaches auth token
│       │   ├── socket.ts                WebSocket connect, reconnect, parse
│       │   └── endpoints.ts             URL constants
│       ├── pages/
│       │   ├── Login.tsx
│       │   ├── Analyzer.tsx             problem form + editor + submit
│       │   ├── Results.tsx              analysis panel, bugs, complexity
│       │   ├── Optimization.tsx         diff view, benchmark, apply
│       │   ├── History.tsx
│       │   └── Training.tsx             start training, live loss chart
│       ├── components/
│       │   ├── editor/
│       │   │   ├── CodeEditor.tsx       Monaco wrapper
│       │   │   ├── DiffViewer.tsx       Monaco diff, original vs optimized
│       │   │   ├── OptimizedCodePanel.tsx  final code, copy button
│       │   │   └── EditorToolbar.tsx
│       │   ├── problem/
│       │   │   ├── ProblemForm.tsx      structured metadata input
│       │   │   └── ProblemPicker.tsx    choose from catalog
│       │   ├── analysis/
│       │   │   ├── AlgorithmCard.tsx    ranked labels + probabilities
│       │   │   ├── ComplexityCard.tsx   time, space, derivation steps
│       │   │   ├── FindingsList.tsx     static findings
│       │   │   ├── CounterexampleCard.tsx
│       │   │   └── MetricsBar.tsx       the three defined metrics
│       │   ├── optimization/
│       │   │   ├── SummaryCard.tsx      headline, explanation, trade-off
│       │   │   ├── ComparisonTable.tsx  original vs optimized rows
│       │   │   ├── ChangeList.tsx       numbered concrete edits
│       │   │   └── VerificationBadge.tsx  verified / not verified
│       │   ├── visualization/
│       │   │   ├── ASTViewer.tsx        collapsible tree
│       │   │   ├── CFGViewer.tsx        node/edge graph
│       │   │   └── ComplexityGraph.tsx  measured runtime vs n
│       │   ├── charts/
│       │   │   └── LiveChart.tsx        Recharts, training loss + progress
│       │   └── common/                  Button, Badge, Loading, ErrorBox
│       ├── hooks/
│       │   ├── useJob.ts
│       │   ├── useProgressSocket.ts
│       │   └── useAuth.ts
│       ├── types/
│       │   └── api.d.ts           ★ hand-mirrored from docs/api-spec.md
│       └── styles/
│
└── backend/
    ├── CMakeLists.txt             [T3 owns. T1/T4 send target lines, do not edit]
    ├── config.json                [T3] port, db path, thread count, limits
    │
    ├── db/                        ══════ T3 ══════
    │   ├── schema.sql
    │   └── seed.sql               problem catalog + reference solutions
    │
    ├── src/
    │   ├── main.cpp               [T3] boot Drogon, DB, thread pool, load model
    │   │
    │   ├── api/                   ══════ T3 ══════  HTTP and WebSocket only
    │   │   ├── HealthController.cpp/.hpp
    │   │   ├── AuthController.cpp/.hpp      signup, login, logout, me
    │   │   ├── JobController.cpp/.hpp       create, get, list, cancel
    │   │   ├── ExecuteController.cpp/.hpp   synchronous sandbox run
    │   │   ├── ProblemController.cpp/.hpp   catalog listing
    │   │   ├── ModelController.cpp/.hpp     train, list models, activate
    │   │   ├── ProgressSocket.cpp/.hpp      /ws/jobs/{id}
    │   │   └── Middleware.cpp/.hpp          token check, CORS, rate limit
    │   │
    │   ├── services/              ══════ T3 ══════  orchestration, threading
    │   │   ├── JobManager.cpp/.hpp          queue, dispatch, status, cancel
    │   │   ├── ThreadPool.hpp
    │   │   ├── ProgressBroadcaster.cpp/.hpp fan out events to sockets
    │   │   └── AuthService.cpp/.hpp         Argon2 hashing, session tokens
    │   │
    │   ├── storage/               ══════ T3 ══════  SQLite access only
    │   │   ├── Database.cpp/.hpp
    │   │   ├── UserRepo.cpp/.hpp
    │   │   ├── JobRepo.cpp/.hpp
    │   │   ├── AnalysisRepo.cpp/.hpp
    │   │   ├── ProblemRepo.cpp/.hpp
    │   │   └── ModelRepo.cpp/.hpp
    │   │
    │   ├── engine/                ══════ T4 ══════  deterministic analysis
    │   │   ├── IEngine.hpp        ★ CONTRACT, T3 + T4
    │   │   ├── Engine.cpp/.hpp             orchestrates the 9 steps
    │   │   ├── parse/
    │   │   │   ├── ClangFrontend.cpp/.hpp  libclang invocation
    │   │   │   └── AstBuilder.cpp/.hpp     Clang AST → internal AST
    │   │   ├── ast/
    │   │   │   ├── Node.hpp                internal AST node types
    │   │   │   ├── Traversal.cpp/.hpp      DFS, BFS, visitor
    │   │   │   └── Serializer.cpp/.hpp     AST → JSON for the UI
    │   │   ├── cfg/
    │   │   │   ├── CfgBuilder.cpp/.hpp     basic blocks, edges
    │   │   │   ├── Dominators.cpp/.hpp
    │   │   │   └── Reachability.cpp/.hpp   unreachable code, dead branches
    │   │   ├── complexity/
    │   │   │   ├── LoopAnalyzer.cpp/.hpp   bounds, nesting, stride
    │   │   │   ├── RecurrenceSolver.cpp/.hpp  master theorem cases
    │   │   │   ├── TimeComplexity.cpp/.hpp
    │   │   │   └── SpaceComplexity.cpp/.hpp
    │   │   ├── checks/
    │   │   │   ├── StaticChecks.cpp/.hpp   findings over AST + CFG
    │   │   │   └── rules/                  one file per rule
    │   │   ├── optimize/
    │   │   │   ├── IPass.hpp
    │   │   │   ├── Catalog.cpp/.hpp        pattern → transformation table
    │   │   │   ├── passes/
    │   │   │   │   ├── PairSumToHash.cpp
    │   │   │   │   ├── LinearToBinarySearch.cpp
    │   │   │   │   ├── NaiveToPrefixSum.cpp
    │   │   │   │   ├── RecursionToMemo.cpp
    │   │   │   │   └── MinScanToHeap.cpp
    │   │   │   ├── Templates/              .cpp.tmpl code templates
    │   │   │   └── SummaryBuilder.cpp/.hpp assembles OptimizationSummary
    │   │   └── verify/
    │   │       ├── TestGenerator.cpp/.hpp  random + edge cases
    │   │       ├── Oracle.cpp/.hpp         reference solution comparison
    │   │       └── Benchmark.cpp/.hpp      runtime + memory, before/after
    │   │
    │   ├── sandbox/               ══════ T4 ══════
    │   │   ├── Compiler.cpp/.hpp           g++ invocation, capture errors
    │   │   ├── Runner.cpp/.hpp             fork/exec, stdin/stdout capture
    │   │   └── Limits.cpp/.hpp             rlimit: CPU, memory, file size
    │   │
    │   ├── ml/                    ══════ T1 ══════
    │   │   ├── IPredictor.hpp     ★ CONTRACT, T4 + T1
    │   │   ├── FeatureExtractor.cpp/.hpp   AST/CFG stats → float vector
    │   │   ├── Dataset.cpp/.hpp            load, split, batch
    │   │   ├── MutationEngine.cpp/.hpp     generate labeled variants
    │   │   ├── Model.cpp/.hpp              LibTorch MLP definition
    │   │   ├── Trainer.cpp/.hpp            train loop, emits epoch + loss
    │   │   ├── Predictor.cpp/.hpp          load .pt, ranked prediction
    │   │   └── Metrics.cpp/.hpp            accuracy, confusion matrix
    │   │
    │   └── common/                ══════ T3 owns, all may add ══════
    │       ├── Json.hpp                    nlohmann helpers
    │       ├── Logger.hpp
    │       ├── Errors.hpp                  shared error codes
    │       └── Types.hpp                   JobStatus, PassType, Severity
    │
    ├── data/                      ══════ T1 ══════  training samples
    ├── models/                    ══════ T1 ══════  saved .pt checkpoints
    │
    └── tests/                     ══════ ALL, week 5 ══════
        ├── test_ast.cpp           [T4]
        ├── test_cfg.cpp           [T4]
        ├── test_complexity.cpp    [T4]
        ├── test_optimize.cpp      [T4]
        ├── test_sandbox.cpp       [T4]
        ├── test_features.cpp      [T1]
        ├── test_model.cpp         [T1]
        ├── test_storage.cpp       [T3]
        ├── test_api.cpp           [T3]
        └── fixtures/              sample programs with known answers
```

---

## 5. The three frozen contracts

### 5.1 `engine/IEngine.hpp` (T3 to T4)

T3 includes this file and nothing else from `engine/`.

```cpp
#pragma once
#include <string>
#include <vector>
#include <functional>
#include <optional>

namespace nc {

struct ProblemSpec {
    std::string problem_id;      // empty if custom
    std::string input_type;      // "int_array", "string", "graph", ...
    std::string output_type;     // "bool", "int", "array", ...
    std::string operation;       // "pair_sum", "search", "sort", ...
    long long   max_n = 0;
};

struct AlgorithmGuess { std::string label; float probability; };

struct Complexity {
    std::string time;                      // "O(n^2)"
    std::string space;                     // "O(1)"
    std::vector<std::string> derivation;   // human readable steps
};

struct Finding {
    int line;
    std::string severity;   // "high" | "medium" | "low"
    std::string type;       // "unreachable", "overflow_risk", ...
    std::string message;
};

struct Counterexample {
    std::string input;
    std::string expected_output;
    std::string actual_output;
};

struct BenchmarkResult {
    double before_ms = 0, after_ms = 0;
    long   before_kb = 0, after_kb = 0;
    long long n_used = 0;
};

struct AnalysisResult {
    std::vector<AlgorithmGuess> algorithms;   // ranked, top 3
    Complexity complexity;
    std::vector<Finding> findings;
    std::vector<Counterexample> counterexamples;
    std::string ast_json;
    std::string cfg_json;
    bool optimization_available = false;
    bool success = true;
    std::string error;
};

struct SummaryRow {                        // one comparison line for the UI table
    std::string label;                     // "Time", "Space", "Runtime at n=50000"
    std::string before;
    std::string after;
};

struct OptimizationSummary {
    std::string headline;                  // one sentence, what changed
    std::string explanation;               // 2-4 sentences, why it is faster
    std::vector<SummaryRow> comparison;    // original vs optimized table
    std::vector<std::string> changes;      // numbered list of concrete edits
    std::string tradeoff;                  // what got worse, empty if nothing did
    std::string verification;              // what was run to prove equivalence
    double speedup = 0.0;                  // measured, not theoretical
};

struct OptimizeResult {
    AnalysisResult analysis;
    std::string recommended_algorithm;
    std::string recommended_complexity;
    std::string optimized_code;            // empty when verified == false
    OptimizationSummary summary;
    bool verified = false;                 // passed differential testing
    BenchmarkResult bench;
    bool success = true;
    std::string error;
};

// percent 0..100, stage is a short human label
using ProgressFn = std::function<void(int percent, const std::string& stage)>;

class IEngine {
public:
    virtual ~IEngine() = default;
    virtual AnalysisResult analyze(const std::string& code,
                                   const ProblemSpec& spec,
                                   ProgressFn on_progress) = 0;
    virtual OptimizeResult optimize(const std::string& code,
                                    const ProblemSpec& spec,
                                    ProgressFn on_progress) = 0;
    virtual void cancel() = 0;
};

} // namespace nc
```

### 5.2 `ml/IPredictor.hpp` (T4 to T1)

T4 includes this file and never touches LibTorch directly.

```cpp
#pragma once
#include <string>
#include <vector>
#include "engine/IEngine.hpp"   // for AlgorithmGuess

namespace nc {

class IPredictor {
public:
    virtual ~IPredictor() = default;

    // ast_json and cfg_json come from the engine
    virtual std::vector<float> extractFeatures(const std::string& ast_json,
                                               const std::string& cfg_json) = 0;

    // ranked, highest probability first, length <= k
    virtual std::vector<AlgorithmGuess> predict(const std::vector<float>& features,
                                                int k = 3) = 0;

    virtual bool loadModel(const std::string& checkpoint_path) = 0;
    virtual std::string activeModelVersion() const = 0;
};

} // namespace nc
```

### 5.3 `docs/api-spec.md` (T3 to T2)

The JSON contract. T2 hand-mirrors it into `frontend/src/types/api.d.ts`. If the spec changes, both sides change the same day.

---

## 6. Data model

SQLite. Big artifacts (`.pt` checkpoints, datasets, compiled binaries) live on disk; only paths are stored.

```sql
CREATE TABLE users (
    id            INTEGER PRIMARY KEY,
    username      TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,             -- Argon2id
    created_at    TEXT DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE sessions (
    token      TEXT PRIMARY KEY,
    user_id    INTEGER NOT NULL REFERENCES users(id),
    expires_at TEXT NOT NULL
);

CREATE TABLE problems (                       -- seeded catalog
    id             TEXT PRIMARY KEY,          -- "pair_sum"
    title          TEXT NOT NULL,
    input_type     TEXT, output_type TEXT, operation TEXT,
    max_n          INTEGER,
    optimal_time   TEXT,                      -- "O(n)"
    reference_code TEXT NOT NULL              -- oracle solution
);

CREATE TABLE jobs (
    id          INTEGER PRIMARY KEY,
    user_id     INTEGER REFERENCES users(id),
    type        TEXT CHECK(type IN ('analyze','optimize','train')),
    status      TEXT CHECK(status IN ('queued','running','done','failed','cancelled')),
    problem_id  TEXT REFERENCES problems(id),
    problem_json TEXT,                        -- custom ProblemSpec
    input_code  TEXT,
    progress    INTEGER DEFAULT 0,
    stage       TEXT,
    error       TEXT,
    created_at  TEXT DEFAULT CURRENT_TIMESTAMP,
    finished_at TEXT
);
CREATE INDEX idx_jobs_user ON jobs(user_id, created_at DESC);

CREATE TABLE analyses (
    id               INTEGER PRIMARY KEY,
    job_id           INTEGER NOT NULL REFERENCES jobs(id),
    algorithms_json  TEXT,                    -- ranked list
    time_complexity  TEXT,
    space_complexity TEXT,
    derivation_json  TEXT,
    ast_json         TEXT,
    cfg_json         TEXT,
    model_version    TEXT
);

CREATE TABLE findings (
    id          INTEGER PRIMARY KEY,
    analysis_id INTEGER NOT NULL REFERENCES analyses(id),
    line        INTEGER, severity TEXT, type TEXT, message TEXT
);

CREATE TABLE counterexamples (
    id              INTEGER PRIMARY KEY,
    analysis_id     INTEGER NOT NULL REFERENCES analyses(id),
    input           TEXT, expected_output TEXT, actual_output TEXT
);

CREATE TABLE optimizations (
    id               INTEGER PRIMARY KEY,
    analysis_id      INTEGER NOT NULL REFERENCES analyses(id),
    old_algorithm    TEXT, new_algorithm TEXT,
    old_complexity   TEXT, new_complexity TEXT,
    optimized_code   TEXT, reason TEXT,
    verified         INTEGER DEFAULT 0,
    before_ms REAL, after_ms REAL, before_kb INTEGER, after_kb INTEGER, n_used INTEGER
);

CREATE TABLE models (
    id              INTEGER PRIMARY KEY,
    version         TEXT UNIQUE NOT NULL,     -- "v3-20260410"
    checkpoint_path TEXT NOT NULL,
    accuracy        REAL, loss REAL,
    epochs          INTEGER, dataset_size INTEGER,
    trained_at      TEXT DEFAULT CURRENT_TIMESTAMP,
    is_active       INTEGER DEFAULT 0
);
```

---

## 7. Analysis engine detail (T4)

### 7.1 Parsing

libclang produces the Clang AST. `AstBuilder` walks it and emits a small internal tree with only the node types NeuroCode cares about: function, loop, branch, call, assignment, array access, declaration, return. Roughly 15 node types instead of Clang's several hundred.

Reason for the internal tree: Clang's AST is unstable across versions and far too detailed for feature extraction. A small owned tree keeps `FeatureExtractor` and the optimizer simple.

### 7.2 CFG

Basic blocks with directed edges. Built in one pass over the internal AST. Used for:

| Analysis | DSA used |
|---|---|
| Unreachable code | Graph reachability from entry (BFS) |
| Missing return path | DFS to exit, check all leaves |
| Loop detection | Back edges via dominator relation |
| Infinite loop candidates | Loop with no exit edge and no condition update |

### 7.3 Complexity engine

Deterministic, not learned. Handles these cases explicitly and reports "unknown" otherwise. Reporting "unknown" honestly is better than guessing.

| Pattern | Result |
|---|---|
| `for (i = 0; i < n; i++)` | O(n) |
| Nested independent loops | Product of bounds |
| `for (j = i+1; ...)` inside `for (i ...)` | O(n^2), triangular |
| `while (n > 1) n /= 2` | O(log n) |
| Binary-search shaped loop | O(log n) |
| Recursion with two calls on n/2 plus O(n) merge | O(n log n), master theorem |
| Recursion with two calls on n-1 | O(2^n) |
| STL `sort` call | O(n log n) |
| STL `unordered_map` / `unordered_set` op | O(1) expected |

Space: counts declared containers and their size expressions, plus recursion depth.

Every result carries a `derivation` array so the UI can show why, which is what turns this from a black box into something defensible.

### 7.4 Optimizer

A table, not a generator.

```
(detected algorithm, problem operation, constraint check) → transformation
```

Example rows:

| Detected | Problem | Condition | Transformation | New complexity |
|---|---|---|---|---|
| Brute force pair search | pair_sum | max_n > 5000 | PairSumToHash | O(n) |
| Linear search | search | input sorted | LinearToBinarySearch | O(log n) |
| Repeated range sum | range_sum | queries > 1 | NaiveToPrefixSum | O(1) per query |
| Naive recursion | any | overlapping subproblems | RecursionToMemo | depends |
| Repeated min extraction | scheduling | max_n > 1000 | MinScanToHeap | O(n log n) |

Each transformation fills a `.cpp.tmpl` template with the user's identifiers (function name, parameter names, types), then the result is compiled and differentially tested against the original before it is ever shown. If verification fails, the optimization is suppressed and the job reports the original analysis only.

### 7.5 Summary generation

The optimized code alone is not the deliverable. A student who receives rewritten code without an explanation has learned nothing, and a reviewer cannot judge whether the rewrite is sound. So every optimization ships with a structured summary, assembled by `SummaryBuilder`.

It is built from three sources, none of them a language model:

| Summary field | Where it comes from |
|---|---|
| `headline` | A fixed sentence attached to the transformation in the catalog |
| `explanation` | Template text with the detected identifiers and bounds substituted in |
| `comparison` | Complexity engine (before and after) plus `Benchmark` measurements |
| `changes` | Diff between the original and generated AST, described per node |
| `tradeoff` | Catalog entry, for example "space rises from O(1) to O(n)" |
| `verification` | `Oracle` reports test count, mismatch count, and which edge cases ran |
| `speedup` | `before_ms / after_ms`, measured, never derived from complexity classes |

The `changes` list deserves attention because it is the part that makes the feature educational rather than magical. It is produced by walking both ASTs and recording structural differences:

```
original AST                generated AST           recorded change
────────────────            ─────────────           ───────────────
ForLoop (i)                 RangeFor (x)            "loop over indices replaced with range-for"
  └─ ForLoop (j)            (absent)                "removed nested loop over j (lines 3-5)"
(absent)                    DeclStmt unordered_set  "added unordered_set<int> seen"
BinaryOp a[i]+a[j]==k       CallExpr seen.count()   "pair comparison replaced with complement lookup"
```

Three rules the builder enforces:

1. **No summary without verification.** If `verified == false`, `optimized_code` is empty and the summary is not built at all. The job returns the analysis only.
2. **No theoretical speedups.** The `speedup` field is a ratio of two measured timings on the same machine in the same run. If benchmarking fails, the field is 0 and the UI hides it.
3. **The trade-off is never omitted.** Every catalog entry must declare what gets worse. If a transformation genuinely has no cost, the entry says so explicitly rather than leaving the field blank.

### 7.6 Verification, not proof

```
TestGenerator ──► input set ──┬──► user code ────► output A
                              └──► reference ────► output B
                                        │
                              A != B ──► counterexample
```

Generated inputs: empty, single element, all equal, sorted ascending, sorted descending, maximum values (overflow probing), random small, random large.

This finds bugs. It does not prove their absence, and the UI and report say so.

---

## 8. ML module detail (T1)

### 8.1 Task

Multi-class classification: given an AST and CFG, name the algorithm. Roughly 14 classes, for example brute force pair search, binary search, two pointer, sliding window, BFS, DFS, DP one-dimensional, DP two-dimensional, greedy scan, sorting based, hashing, heap based.

One task, done well. Bug detection is handled by the deterministic side.

### 8.2 Features

A fixed-length float vector from the AST and CFG, roughly 40 to 60 dimensions:

- loop count, maximum nesting depth, loop bound shapes (n, n/2, i to n, constant)
- recursion present, recursive call count, self-call depth
- branch count, CFG node count, edge count, cyclomatic complexity
- container usage counts by type (vector, set, unordered_set, map, unordered_map, queue, stack, priority_queue)
- STL algorithm calls (sort, lower_bound, find, max_element)
- arithmetic operation mix, comparison operator counts
- array index expression shapes (i, i+1, i-1, 2*i, mid)
- pointer/index variable count, two-index patterns

Hand-crafted features are chosen over token embeddings deliberately: they train on a few thousand samples, they run instantly, and every dimension can be explained in the viva. A token transformer would need far more data than this project can produce.

### 8.3 Dataset

Target: 2000 to 4000 labeled samples.

```
~150 hybrid (hand-written + externally imported) reference implementations (12-15 classes)
         │
         ▼
MutationEngine: identifier renaming, loop restructuring (for/while swap),
                variable reordering, equivalent expression rewrites,
                dead statement insertion, container substitution
         │
         ▼
~20 variants per seed, label preserved
         │
         ▼
train / val / test split 70 / 15 / 15, split by SEED not by sample
```

The last point matters. If mutations of the same seed land in both train and test, accuracy is inflated and the result is meaningless. Split at the seed level.

### 8.4 Model

```
input (n_features)
   → Linear(128) → ReLU → Dropout(0.3)
   → Linear(64)  → ReLU → Dropout(0.2)
   → Linear(n_classes)
   → Softmax
```

Cross-entropy loss, Adam, batch 32, early stopping on validation loss. Features standardized using training-set mean and standard deviation, and those statistics are saved with the checkpoint.

Training runs on a worker thread and emits `{epoch, train_loss, val_loss, val_accuracy}` through the same `ProgressFn` mechanism as analysis, so the frontend chart works without new plumbing.

### 8.5 Reporting

Always top-3 with probabilities. If the top probability is below a threshold (start at 0.5), the UI shows "low confidence" and the deterministic complexity result is presented as the primary finding.

---

## 9. Concurrency and safety

**Threading.** Drogon's event loop handles HTTP. Jobs run on a separate `ThreadPool` (default 4 workers). Long analysis never blocks a request thread. Cancellation uses an `std::atomic<bool>` checked between engine steps.

**Sandbox.** User code compiles and runs in a forked process with:

| Limit | Value |
|---|---|
| CPU time | 5 s (analysis), 10 s (benchmark) |
| Address space | 256 MB |
| Output size | 1 MB |
| File writes | none |
| Network | none |
| Process count | 1 |

Compilation itself is also limited (10 s) because template-heavy input can hang a compiler.

Isolation is done with plain POSIX primitives, no containers:

- `fork()` then `setrlimit()` for CPU time, address space, output size, and process count before `execv()`
- `chdir()` into a per-job scratch directory that is deleted afterwards
- `dup2()` to redirect stdin, stdout and stderr into pipes
- `alarm()` plus a `waitpid()` timeout as a second line of defense, with `SIGKILL` on expiry
- the child drops to an unprivileged user where the deployment allows it

This is weaker than container isolation and the report says so. It is sufficient for a single-machine academic deployment where submissions are not adversarial.

**Auth.** Argon2id password hashing via libsodium. Opaque random session tokens in the `sessions` table, 7 day expiry, sent as `Authorization: Bearer <token>`. No JWT, no roles, no password reset. Auth is not where the marks are.

---

## 10. DSA mapping

For the project defense.

| Component | Data structure / algorithm |
|---|---|
| Internal AST | N-ary tree, visitor traversal |
| AST traversal | DFS (preorder, postorder), BFS |
| CFG | Directed graph, adjacency list |
| Unreachable code | Graph reachability, BFS from entry |
| Loop detection | Dominator tree, back edge detection |
| Variable and symbol tracking | Hash table |
| Call graph | Directed graph, topological sort for ordering |
| Complexity derivation | Recurrence relations, master theorem |
| Algorithm pattern matching | Tree pattern matching against catalog |
| Candidate ranking | Priority queue on estimated gain |
| Code transformation | Tree manipulation, template instantiation |
| Test case generation | Constrained random generation, edge enumeration |
| Memoization detection | Overlapping subproblem detection on the call tree |

The claim to make: the analysis layer is not a wrapper around DSA concepts, it is built out of them.

---

## 11. Risks

| Risk | Impact | Mitigation | Owner |
|---|---|---|---|
| LibTorch does not build | Kills the ML half | Get it compiling in week 1 day 1 to 4. Fallback: hand-written MLP with manual backprop, or mlpack | T1 |
| libclang integration harder than expected | Kills the analysis half | Prototype on day 2. Fallback: restrict input to a C-like subset and use a simple recursive descent parser | T4 |
| Not enough training data | Model accuracy near chance | MutationEngine started week 2, not week 3 | T1 |
| T1 to T4 inference handoff slips | Demo has no ML in it | `IPredictor` stub returns random labels from week 1, so the wiring is done and tested long before the real model exists | T1 + T4 |
| Generated code is wrong | Worst possible demo failure | Never show unverified output. `verified=false` suppresses the optimization entirely | T4 |
| Scope creep back toward the original plan | Nothing finishes | Section "Out of scope" in the README is binding | All |

### Week 2 go/no-go

By the end of week 2, a user must be able to paste code in the browser, have it reach the C++ engine, and see a real result come back. If that does not work on the Friday of week 2, drop the ML model and ship a fully deterministic analyzer. A complete rule-based system scores better than a half-finished neural one that does not run in the demo.
