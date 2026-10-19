# NeuroCode frontend (T2)

React 18 + TypeScript + Vite + Tailwind. Monaco for code, Recharts for charts.

## Run

```bash
npm install
cp .env.example .env     # VITE_USE_MOCK=true works with no backend
npm run dev              # http://localhost:5173
```

Any username (3+ chars) and password (8+ chars) signs in while mock mode is on.

## Switch to the real backend

Set `VITE_USE_MOCK=false` in `.env`. Vite proxies `/api` and `/ws` to `http://localhost:8080` (see `vite.config.ts`).

## Pages

| Route | File | What it does |
|---|---|---|
| `/login` | `pages/Login.tsx` | Sign in / sign up |
| `/analyze` | `pages/Analyzer.tsx` | Monaco editor, problem catalog or custom spec, examples, editor settings, sandbox console, submit |
| `/jobs/:id` | `pages/Results.tsx` | Live 9-step progress, metrics, complexity, algorithms, findings, counterexamples, AST/CFG, growth curves |
| `/optimize/:id` | `pages/Optimization.tsx` | Summary, speedup, trade-off, before/after, change list, diff, code, benchmark |
| `/history` | `pages/History.tsx` | Search and filter all jobs |
| `/training` | `pages/Training.tsx` | Presets and hyperparameters, live loss chart, model list and activation |

## Assumptions to reconcile with `docs/api-spec.md` (T3)

`src/types/api.d.ts` and `src/api/endpoints.ts` are my guess at the contract. IEngine.hpp fixes the result shapes; everything else below is invented and must be confirmed.

- Endpoints: `POST /auth/login|signup|logout`, `GET /auth/me`, `POST|GET /jobs`, `GET /jobs/{id}`, `POST /jobs/{id}/cancel`, `GET /problems`, `POST /execute`, `GET /models`, `POST /models/train`, `POST /models/{id}/activate`.
- `POST /jobs` returns `{ job_id }`; `GET /jobs/{id}` returns the job row with `result` attached once done.
- WebSocket `/ws/jobs/{id}?token=...` sends `{type:"progress"|"epoch"|"done"|"error", ...}`. The token is a query parameter because browsers cannot set headers on a WebSocket.
- `ast_json` is `{type, label?, line?, children?[]}`. `cfg_json` is `{nodes:[{id,label,kind?,line?}], edges:[{from,to,label?}]}`.
- Training request: `{epochs, learning_rate, batch_size, early_stopping_patience}`.
- `MetricsBar` shows model confidence, findings, counterexamples. The architecture doc says "the three defined metrics" without naming them. Change it in one file if the group defined others.
- `ComplexityGraph` draws reference curves, not measured timings, because IEngine returns no runtime-vs-n series. Ask T4 to add one if you want real data.
