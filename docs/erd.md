# NeuroCode Data Model (ERD)

Source of truth: `docs/architecture.md` section 6. This diagram mirrors that schema.
SQLite stores rows; large artifacts (`.pt` checkpoints, datasets, compiled binaries) live on disk and only their paths are stored.

```mermaid
erDiagram
    users ||--o{ sessions : "logs in with"
    users |o--o{ jobs : "submits"
    problems |o--o{ jobs : "is solved in"
    jobs ||--o| analyses : "produces"
    analyses ||--o{ findings : "reports"
    analyses ||--o{ counterexamples : "reports"
    analyses ||--o| optimizations : "may lead to"
    models ||..o{ analyses : "classified by (model_version)"

    users {
        int id PK
        text username UK
        text password_hash "Argon2id"
        text created_at
    }

    sessions {
        text token PK "opaque random token"
        int user_id FK
        text expires_at "7 day expiry"
    }

    problems {
        text id PK "e.g. pair_sum"
        text title
        text input_type
        text output_type
        text operation
        int max_n
        text optimal_time "e.g. O(n)"
        text reference_code "oracle solution"
    }

    jobs {
        int id PK
        int user_id FK
        text type "analyze | optimize | train"
        text status "queued | running | done | failed | cancelled"
        text problem_id FK "null for custom problems"
        text problem_json "custom ProblemSpec"
        text input_code
        int progress "0 to 100"
        text stage
        text error
        text created_at
        text finished_at
    }

    analyses {
        int id PK
        int job_id FK
        text algorithms_json "ranked top 3"
        text time_complexity
        text space_complexity
        text derivation_json
        text ast_json
        text cfg_json
        text model_version "matches models.version"
    }

    findings {
        int id PK
        int analysis_id FK
        int line
        text severity "high | medium | low"
        text type
        text message
    }

    counterexamples {
        int id PK
        int analysis_id FK
        text input
        text expected_output
        text actual_output
    }

    optimizations {
        int id PK
        int analysis_id FK
        text old_algorithm
        text new_algorithm
        text old_complexity
        text new_complexity
        text optimized_code
        text reason
        int verified "0 or 1"
        real before_ms
        real after_ms
        int before_kb
        int after_kb
        int n_used
    }

    models {
        int id PK
        text version UK "e.g. v3-20260410"
        text checkpoint_path "path to .pt on disk"
        real accuracy
        real loss
        int epochs
        int dataset_size
        text trained_at
        int is_active "0 or 1, one active model"
    }
```

## How to read it

| Symbol | Meaning |
|---|---|
| `\|\|--o{` | one to zero-or-many |
| `\|o--o{` | zero-or-one to zero-or-many (the foreign key may be null) |
| `\|\|--o\|` | one to zero-or-one |
| dotted line | linked by value, not by a foreign key |

## Relationships

| From | To | Cardinality | Notes |
|---|---|---|---|
| users | sessions | 1 to many | One user can be logged in on several devices |
| users | jobs | 0..1 to many | `user_id` may be null if auth is skipped (hardcoded user) |
| problems | jobs | 0..1 to many | `problem_id` is null when the user describes a custom problem in `problem_json` |
| jobs | analyses | 1 to 0..1 | analyze and optimize jobs produce one analysis; train jobs produce none |
| analyses | findings | 1 to many | Static check results |
| analyses | counterexamples | 1 to many | Differential testing mismatches |
| analyses | optimizations | 1 to 0..1 | Only when an optimization was found and verified |
| models | analyses | 1 to many | By value: `analyses.model_version` stores `models.version`, so old analyses keep their record even if a model row is removed |

## Open points for T3

1. **`optimizations` is missing the summary.** `OptimizationSummary` in `engine/IEngine.hpp` has `headline`, `explanation`, `comparison`, `changes`, `tradeoff`, `verification` and `speedup`. None of these have a column. Simplest fix: add one `summary_json TEXT` column.
2. **No link from a training job to the model it produced.** If the History or Training page should show "job 42 produced model v3", add `job_id INTEGER REFERENCES jobs(id)` to `models`.
3. **`jobs ||--o| analyses` is a rule, not enforced.** The schema allows several analyses per job. Add `UNIQUE` on `analyses.job_id` if exactly one is intended.
4. **Shortcut for week 2:** storing the whole `AnalysisResult` as one `result_json` column on `jobs` is enough to make the API work. The normalized tables above can be filled in later without changing the API.
