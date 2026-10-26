# NeuroCode API Specification

Version 1.0. Owner: T3. Consumer: T2.

**This file is the contract.** `frontend/src/types/api.d.ts` mirrors it by hand. Any change here is announced in the group chat the same day and both sides update together.

Base URL: `http://localhost:8080/api/v1`
Content type: `application/json; charset=utf-8` on every request and response.

---

## 1. Conventions

**Auth.** Every endpoint except `/health`, `/auth/signup`, `/auth/login` and `/problems` requires:

```
Authorization: Bearer <token>
```

**Errors.** Every failure returns the same envelope.

```json
{
  "error": {
    "code": "VALIDATION_FAILED",
    "message": "code field must not be empty",
    "field": "code"
  }
}
```

| HTTP | code | Meaning |
|---|---|---|
| 400 | `VALIDATION_FAILED` | Bad or missing field. `field` names it |
| 401 | `UNAUTHENTICATED` | Missing, invalid, or expired token |
| 403 | `FORBIDDEN` | Job belongs to another user |
| 404 | `NOT_FOUND` | No such job, model, or problem |
| 409 | `USERNAME_TAKEN` | Signup conflict |
| 413 | `CODE_TOO_LARGE` | Source exceeds 64 KB |
| 429 | `RATE_LIMITED` | More than 30 jobs per hour per user |
| 500 | `INTERNAL` | Unhandled server error |
| 503 | `MODEL_UNAVAILABLE` | No active model loaded |

**Timestamps.** ISO 8601 UTC, for example `2026-04-12T09:31:07Z`.

**IDs.** Jobs and models use integers. Problems use string slugs.

---

## 2. Health

### `GET /health`

No auth.

```json
{
  "status": "ok",
  "db": "ok",
  "model_loaded": true,
  "model_version": "v3-20260410",
  "queue_depth": 2,
  "uptime_s": 4831
}
```

`status` is `"ok"` or `"degraded"`. Degraded means the API is up but something behind it is not, for example the model failed to load.

---

## 3. Auth

### `POST /auth/signup`

```json
{ "username": "ahmed", "password": "at-least-8-chars" }
```

201 Created:

```json
{
  "token": "b7f2...",
  "expires_at": "2026-04-19T09:31:07Z",
  "user": { "id": 1, "username": "ahmed", "created_at": "2026-04-12T09:31:07Z" }
}
```

Errors: 409 `USERNAME_TAKEN`, 400 `VALIDATION_FAILED` (username 3 to 32 chars, password min 8).

### `POST /auth/login`

Same request body. 200 with the same response shape. 401 `UNAUTHENTICATED` on wrong credentials. The message is deliberately generic, it never says whether the username exists.

### `POST /auth/logout`

Empty body. 204 No Content. Deletes the session row.

### `GET /auth/me`

```json
{ "id": 1, "username": "ahmed", "created_at": "2026-04-12T09:31:07Z" }
```

---

## 4. Problems

### `GET /problems`

No auth. Returns the seeded catalog used for oracle verification.

```json
{
  "problems": [
    {
      "id": "pair_sum",
      "title": "Pair with given sum",
      "input_type": "int_array",
      "output_type": "bool",
      "operation": "pair_sum",
      "max_n": 100000,
      "optimal_time": "O(n)"
    }
  ]
}
```

### `GET /problems/{id}`

Same object plus `statement` (a short description for display). The reference solution is never sent to the client.

404 `NOT_FOUND` if the slug is unknown.

---

## 5. Jobs

The central resource. Analysis, optimization and training are all jobs.

### `POST /jobs`

Creates a job and returns immediately. The work runs on a background thread.

**Request, using the catalog:**

```json
{
  "type": "analyze",
  "language": "cpp",
  "code": "bool solve(vector<int>& a, int k) { ... }",
  "problem_id": "pair_sum"
}
```

**Request, custom problem:**

```json
{
  "type": "optimize",
  "language": "cpp",
  "code": "...",
  "problem": {
    "input_type": "int_array",
    "output_type": "bool",
    "operation": "pair_sum",
    "max_n": 100000
  }
}
```

| Field | Type | Required | Notes |
|---|---|---|---|
| `type` | `"analyze"` \| `"optimize"` | yes | `"train"` is created through `/train`, not here |
| `language` | `"cpp"` | yes | Only value accepted in v1 |
| `code` | string | yes | Max 64 KB |
| `problem_id` | string | one of the two | Slug from `/problems` |
| `problem` | ProblemSpec | one of the two | Custom metadata |

**202 Accepted:**

```json
{
  "job_id": 42,
  "status": "queued",
  "created_at": "2026-04-12T09:31:07Z",
  "ws_url": "/api/v1/ws/jobs/42"
}
```

Errors: 400, 413 `CODE_TOO_LARGE`, 429 `RATE_LIMITED`.

### `GET /jobs/{id}`

Poll this, or listen on the WebSocket. Both are supported; the socket is preferred and polling is the fallback.

**While running:**

```json
{
  "job_id": 42,
  "type": "analyze",
  "status": "running",
  "progress": 45,
  "stage": "complexity analysis",
  "created_at": "2026-04-12T09:31:07Z",
  "finished_at": null,
  "result": null
}
```

`status` is one of `queued`, `running`, `done`, `failed`, `cancelled`.

**When done, `type: "analyze"`:**

```json
{
  "job_id": 42,
  "type": "analyze",
  "status": "done",
  "progress": 100,
  "stage": "complete",
  "created_at": "2026-04-12T09:31:07Z",
  "finished_at": "2026-04-12T09:31:19Z",
  "result": {
    "algorithms": [
      { "label": "brute_force_pair_search", "probability": 0.94 },
      { "label": "two_pointer",             "probability": 0.04 },
      { "label": "sliding_window",          "probability": 0.02 }
    ],
    "low_confidence": false,
    "model_version": "v3-20260410",

    "complexity": {
      "time": "O(n^2)",
      "space": "O(1)",
      "derivation": [
        "outer loop runs n times (line 2)",
        "inner loop runs n - i - 1 times (line 3)",
        "sum over i gives n(n-1)/2",
        "no heap allocation detected"
      ]
    },

    "findings": [
      {
        "line": 14,
        "severity": "medium",
        "type": "overflow_risk",
        "message": "a[i] + a[j] may overflow int for values near INT_MAX"
      }
    ],

    "counterexamples": [
      {
        "input": "a = [1, 3, 5]\nk = 8",
        "expected_output": "true",
        "actual_output": "false"
      }
    ],

    "execution": {
      "compiled": true,
      "compile_error": null,
      "tests_run": 200,
      "tests_passed": 199
    },

    "ast": { "type": "Function", "name": "solve", "children": [] },
    "cfg": { "nodes": [], "edges": [] },

    "optimization_available": true
  }
}
```

**When done, `type: "optimize"`:** the same `result` object with four extra keys.

```json
{
  "optimization": {
    "original_algorithm": "brute_force_pair_search",
    "original_complexity": "O(n^2)",
    "recommended_algorithm": "hash_set_lookup",
    "recommended_complexity": "O(n)",

    "optimized_code": "bool solve(vector<int>& a, int k) {\n    unordered_set<int> seen;\n    for (int x : a) {\n        if (seen.count(k - x)) return true;\n        seen.insert(x);\n    }\n    return false;\n}",

    "summary": {
      "headline": "Replaced the inner scan with a hash set lookup.",
      "explanation": "The original checks every pair, so the work grows with the square of the input size. The new version stores each value as it passes and asks the set whether the complement k - x has already been seen, which answers the same question in one pass.",
      "comparison": [
        { "label": "Algorithm",            "before": "Brute force pair search", "after": "Hash set lookup" },
        { "label": "Time",                 "before": "O(n^2)",   "after": "O(n) expected" },
        { "label": "Space",                "before": "O(1)",     "after": "O(n)" },
        { "label": "Runtime at n = 50000", "before": "2841 ms",  "after": "8.4 ms" },
        { "label": "Memory",               "before": "412 KB",   "after": "2180 KB" }
      ],
      "changes": [
        "Removed the nested loop over j (lines 3 to 5)",
        "Added an unordered_set<int> seen to record values already visited",
        "Replaced the a[i] + a[j] == k test with a complement lookup"
      ],
      "tradeoff": "Memory rises from constant to linear in n. At the stated bound of n = 100000 this is roughly 400 KB, which is acceptable.",
      "verification": "Compiled successfully and produced identical output to the original on 200 generated inputs, including empty array, single element, all-equal values, and values near INT_MAX.",
      "speedup": 338.2
    },

    "verified": true,
    "verification": { "tests_run": 200, "mismatches": 0 },
    "benchmark": {
      "n_used": 50000,
      "before_ms": 2841.3,
      "after_ms": 8.4,
      "speedup": 338.2,
      "before_kb": 412,
      "after_kb": 2180
    }
  }
}
```

### Rendering rules for T2

| Condition | What the UI shows |
|---|---|
| `verified: true` | Diff view, optimized code panel with copy button, full summary card |
| `verified: false` | Analysis only, plus "No verified optimization found". `optimized_code` and `summary` are both `null`. Never render unverified generated code |
| `summary.speedup` is `0` | Hide the speedup figure. Benchmarking failed; the rest of the summary is still valid |
| `summary.tradeoff` is `""` | Render "No significant trade-off" rather than an empty row |

The summary is the primary output of an optimize job, not a footnote next to the code. Give it equal visual weight to the diff.

**When failed:**

```json
{
  "job_id": 42,
  "status": "failed",
  "error": { "code": "COMPILE_ERROR", "message": "line 7: expected ';' before '}'" },
  "result": null
}
```

Job-level error codes: `COMPILE_ERROR`, `PARSE_ERROR`, `TIMEOUT`, `SANDBOX_ERROR`, `MODEL_UNAVAILABLE`, `INTERNAL`.

### `GET /jobs`

History. Query params: `limit` (default 20, max 100), `offset` (default 0), `type`, `status`.

```json
{
  "jobs": [
    {
      "job_id": 42,
      "type": "analyze",
      "status": "done",
      "problem_id": "pair_sum",
      "algorithm": "brute_force_pair_search",
      "time_complexity": "O(n^2)",
      "created_at": "2026-04-12T09:31:07Z"
    }
  ],
  "total": 37,
  "limit": 20,
  "offset": 0
}
```

Summary rows only. Full results come from `GET /jobs/{id}`.

### `DELETE /jobs/{id}`

Cancels a queued or running job. 204 No Content. 409 if already finished.

---

## 6. WebSocket: live progress

### `WS /api/v1/ws/jobs/{id}`

Token is sent as a query parameter because browsers cannot set headers on a WebSocket handshake:

```
ws://localhost:8080/api/v1/ws/jobs/42?token=b7f2...
```

Server-to-client messages. Client sends nothing.

**Progress (analysis or optimization):**

```json
{ "event": "progress", "job_id": 42, "percent": 45, "stage": "complexity analysis" }
```

**Progress (training):**

```json
{
  "event": "epoch",
  "job_id": 51,
  "epoch": 12,
  "epochs_total": 50,
  "train_loss": 0.412,
  "val_loss": 0.498,
  "val_accuracy": 0.837
}
```

**Completion:**

```json
{ "event": "done", "job_id": 42 }
```

The socket closes after `done`. The client then calls `GET /jobs/{id}` for the full result. Results are never sent over the socket, which keeps it small and keeps one source of truth.

**Failure:**

```json
{ "event": "failed", "job_id": 42, "error": { "code": "COMPILE_ERROR", "message": "..." } }
```

**Reconnect rule for T2:** if the socket drops, fall back to polling `GET /jobs/{id}` every 2 seconds. Never rely on the socket alone.

---

## 7. Direct execution

### `POST /execute`

Synchronous, for the "run it yourself" panel. Not a job.

```json
{ "language": "cpp", "code": "...", "stdin": "3\n1 2 3\n", "timeout_ms": 5000 }
```

```json
{
  "compiled": true,
  "compile_error": null,
  "exit_code": 0,
  "stdout": "6\n",
  "stderr": "",
  "execution_time_ms": 13.4,
  "memory_kb": 12400,
  "timed_out": false
}
```

`timeout_ms` is clamped to 10000. Compile failure returns 200 with `compiled: false` and the compiler message, not an HTTP error, because the request itself succeeded.

---

## 8. Model training and management

### `POST /train`

Starts a training job. Returns the same 202 shape as `POST /jobs`.

```json
{ "epochs": 50, "batch_size": 32, "learning_rate": 0.001, "dataset": "default" }
```

All fields optional. Defaults come from `config.json`.

### `GET /models`

```json
{
  "models": [
    {
      "id": 3,
      "version": "v3-20260410",
      "accuracy": 0.871,
      "loss": 0.412,
      "epochs": 50,
      "dataset_size": 3240,
      "trained_at": "2026-04-10T14:22:00Z",
      "is_active": true
    }
  ]
}
```

### `POST /models/{id}/activate`

Loads that checkpoint into the running predictor and flips `is_active`. 200 with the updated model object. 404 if the checkpoint file is missing.

### `GET /models/{id}/metrics`

```json
{
  "version": "v3-20260410",
  "accuracy": 0.871,
  "per_class": [
    { "label": "binary_search", "precision": 0.91, "recall": 0.88, "support": 210 }
  ],
  "confusion_matrix": {
    "labels": ["binary_search", "two_pointer"],
    "matrix": [[185, 12], [9, 196]]
  }
}
```

This feeds the evaluation section of the report, so build it even if the UI does not display it.

---

## 9. Shared enums

T2 mirrors these exactly.

```typescript
type JobType    = "analyze" | "optimize" | "train";
type JobStatus  = "queued" | "running" | "done" | "failed" | "cancelled";
type Severity   = "high" | "medium" | "low";

interface SummaryRow { label: string; before: string; after: string; }

interface OptimizationSummary {
  headline: string;
  explanation: string;
  comparison: SummaryRow[];
  changes: string[];
  tradeoff: string;
  verification: string;
  speedup: number;          // 0 means benchmarking failed, hide it
}

type FindingType =
  | "unreachable" | "missing_return" | "overflow_risk"
  | "off_by_one_suspect" | "unused_variable" | "infinite_loop_suspect"
  | "uninitialized_use" | "inefficient_container";

type AlgorithmLabel =
| "binary_search" | "brute_force_pair_search" | "dp"
| "graph_traversal" | "greedy_scan" | "hashing
| "heap_based" | "linear_search" | "naive_recursion"
| "sliding_window" | "sorting_based" | "two_pointer" | "unknown";
```

---

## 10. Stub contract for week 1

Before the engine exists, `POST /jobs` returns a real `job_id` and `GET /jobs/{id}` returns a fixed, valid response after a 3 second simulated delay, stepping through progress values. T2 builds every page against this and never waits on T4 or T1.

The stub is removed in week 2 when the real engine lands. The JSON shape does not change when it does. That is the entire point of writing this file first.
