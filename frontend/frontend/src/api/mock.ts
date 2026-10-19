// Mock engine so T2 can build and demo the whole UI before T3/T4 land. Enable with VITE_USE_MOCK=true.
import type {
  AnalysisResult, EpochMetrics, Job, ModelInfo, OptimizeResult, Problem, TrainRequest, TrainResult, WsEvent,
} from '../types/api';
import { PIPELINE } from '../lib/pipeline';

const wait = (ms = 200) => new Promise<void>((r) => setTimeout(r, ms));

const PROBLEMS: Problem[] = [
  { id: 'pair_sum', title: 'Pair with target sum', input_type: 'int_array', output_type: 'bool', operation: 'pair_sum', max_n: 100000, optimal_time: 'O(n)', description: 'Does any pair of elements add up to k?' },
  { id: 'search', title: 'Search in sorted array', input_type: 'int_array', output_type: 'int', operation: 'search', max_n: 1000000, optimal_time: 'O(log n)', description: 'Return the index of a target, or -1.' },
  { id: 'range_sum', title: 'Range sum queries', input_type: 'int_array', output_type: 'int', operation: 'range_sum', max_n: 200000, optimal_time: 'O(1) per query', description: 'Sum of a[l..r], many queries.' },
  { id: 'scheduling', title: 'Task scheduling by priority', input_type: 'int_array', output_type: 'array', operation: 'scheduling', max_n: 50000, optimal_time: 'O(n log n)', description: 'Repeatedly take the smallest-deadline task.' },
];

let models: ModelInfo[] = [
  { id: 1, version: 'v1-20260320', accuracy: 0.71, loss: 0.82, epochs: 40, dataset_size: 1200, trained_at: '2026-03-20T10:00:00Z', is_active: false },
  { id: 2, version: 'v2-20260402', accuracy: 0.83, loss: 0.51, epochs: 80, dataset_size: 2400, trained_at: '2026-04-02T10:00:00Z', is_active: false },
  { id: 3, version: 'v3-20260410', accuracy: 0.88, loss: 0.37, epochs: 120, dataset_size: 2840, trained_at: '2026-04-10T10:00:00Z', is_active: true },
];

interface Rec { job: Job; started: number; duration: number; train?: TrainRequest; modelAdded?: boolean }
const recs: Rec[] = [];
let seq = 1;

const AST = {
  type: 'Function', label: 'hasPairSum', line: 4, children: [
    { type: 'Declaration', label: 'a: const vector<int>&', line: 4 },
    { type: 'Declaration', label: 'k: int', line: 4 },
    { type: 'Loop', label: 'for i', line: 5, children: [
      { type: 'Loop', label: 'for j = i + 1', line: 6, children: [
        { type: 'Branch', label: 'if a[i] + a[j] == k', line: 7, children: [
          { type: 'ArrayAccess', label: 'a[i]', line: 7 }, { type: 'ArrayAccess', label: 'a[j]', line: 7 },
          { type: 'Return', label: 'true', line: 7 },
        ] },
      ] },
    ] },
    { type: 'Return', label: 'false', line: 10 },
  ],
};
const CFG = {
  nodes: [
    { id: 0, label: 'entry', kind: 'entry' }, { id: 1, label: 'i = 0', kind: 'block', line: 5 },
    { id: 2, label: 'i < n ?', kind: 'loop', line: 5 }, { id: 3, label: 'j = i + 1', kind: 'block', line: 6 },
    { id: 4, label: 'j < n ?', kind: 'loop', line: 6 }, { id: 5, label: 'a[i] + a[j] == k ?', kind: 'branch', line: 7 },
    { id: 6, label: 'return true', kind: 'block', line: 7 }, { id: 7, label: 'j++', kind: 'block', line: 6 },
    { id: 8, label: 'i++', kind: 'block', line: 5 }, { id: 9, label: 'return false', kind: 'block', line: 10 },
    { id: 10, label: 'exit', kind: 'exit' },
  ],
  edges: [
    { from: 0, to: 1 }, { from: 1, to: 2 }, { from: 2, to: 3, label: 'yes' }, { from: 2, to: 9, label: 'no' },
    { from: 3, to: 4 }, { from: 4, to: 5, label: 'yes' }, { from: 4, to: 8, label: 'no' },
    { from: 5, to: 6, label: 'yes' }, { from: 5, to: 7, label: 'no' }, { from: 7, to: 4 }, { from: 8, to: 2 },
    { from: 6, to: 10 }, { from: 9, to: 10 },
  ],
};

function analysisFor(code: string): AnalysisResult {
  const loops = (code.match(/\b(for|while)\b/g) || []).length;
  const fib = (code.match(/fib\(/g) || []).length >= 3;
  const binary = /\bmid\b/.test(code);
  const base = { counterexamples: [], ast_json: JSON.stringify(AST), cfg_json: JSON.stringify(CFG), success: true, error: '' };
  if (fib) return { ...base, algorithms: [{ label: 'Naive recursion', probability: 0.81 }, { label: 'DP one-dimensional', probability: 0.12 }, { label: 'Divide and conquer', probability: 0.04 }],
    complexity: { time: 'O(2^n)', space: 'O(n)', derivation: ['Two recursive calls, each on n - 1', 'Recurrence T(n) = 2T(n - 1) + O(1)', 'Solves to O(2^n)', 'Recursion depth n gives O(n) stack space'] },
    findings: [{ line: 3, severity: 'high', type: 'overflow_risk', message: 'fib(n) exceeds 64 bits for n > 92.' }, { line: 2, severity: 'medium', type: 'recomputation', message: 'Overlapping subproblems: fib(n - 2) is recomputed inside fib(n - 1).' }],
    optimization_available: true };
  if (binary) return { ...base, algorithms: [{ label: 'Binary search', probability: 0.93 }, { label: 'Two pointer', probability: 0.05 }, { label: 'Greedy scan', probability: 0.01 }],
    complexity: { time: 'O(log n)', space: 'O(1)', derivation: ['Loop halves the range [lo, hi] each iteration', 'Halving loop runs at most log2(n) times', 'Only scalar variables are declared'] },
    findings: [], optimization_available: false };
  if (loops >= 2) return { ...base, algorithms: [{ label: 'Brute force pair search', probability: 0.74 }, { label: 'Two pointer', probability: 0.15 }, { label: 'Hashing', probability: 0.06 }],
    complexity: { time: 'O(n^2)', space: 'O(1)', derivation: ['Outer loop runs i from 0 to n', 'Inner loop starts at i + 1, so the pair count is n(n - 1) / 2', 'Triangular nested loops give O(n^2)', 'No containers declared, so space is O(1)'] },
    findings: [{ line: 7, severity: 'medium', type: 'overflow_risk', message: 'a[i] + a[j] can overflow int when both values are near INT_MAX.' }, { line: 6, severity: 'low', type: 'signedness', message: 'size_t index compared with signed values elsewhere.' }],
    counterexamples: [{ input: 'a = [2147483647, 1], k = -2147483648', expected_output: 'false', actual_output: 'true' }],
    optimization_available: true };
  return { ...base, algorithms: [{ label: 'Greedy scan', probability: 0.44 }, { label: 'Sliding window', probability: 0.31 }, { label: 'Hashing', probability: 0.1 }],
    complexity: { time: 'O(n)', space: 'O(1)', derivation: ['Single loop from 0 to n', 'Constant work per iteration'] },
    findings: [{ line: 5, severity: 'low', type: 'unreachable', message: 'Code after the return is never executed.' }], optimization_available: false };
}

function optimizeFor(code: string): OptimizeResult {
  const analysis = analysisFor(code);
  const fib = analysis.complexity.time === 'O(2^n)';
  const optimized = fib
    ? `#include <vector>\nusing namespace std;\n\nlong long fib(int n) {\n    vector<long long> memo(n + 1, -1);\n    return fibMemo(n, memo);\n}\n`
    : `#include <vector>\n#include <unordered_set>\nusing namespace std;\n\nbool hasPairSum(const vector<int>& a, int k) {\n    unordered_set<int> seen;\n    for (int x : a) {\n        if (seen.count(k - x)) return true;\n        seen.insert(x);\n    }\n    return false;\n}\n`;
  if (!analysis.optimization_available) return { analysis, recommended_algorithm: '', recommended_complexity: '', optimized_code: '', summary: { headline: '', explanation: '', comparison: [], changes: [], tradeoff: '', verification: '', speedup: 0 }, verified: false, bench: { before_ms: 0, after_ms: 0, before_kb: 0, after_kb: 0, n_used: 0 }, success: true, error: '' };
  return {
    analysis, recommended_algorithm: fib ? 'Memoized recursion' : 'Hash set complement lookup', recommended_complexity: fib ? 'O(n)' : 'O(n)',
    optimized_code: optimized, verified: true, bench: { before_ms: fib ? 1840 : 412.6, after_ms: fib ? 0.04 : 3.1, before_kb: 2048, after_kb: fib ? 2200 : 6400, n_used: fib ? 45 : 50000 },
    summary: {
      headline: fib ? 'Cached each fib(n) result so it is computed once.' : 'Replaced the nested pair search with a single pass and a hash set.',
      explanation: fib ? 'The naive version recomputes the same subproblems exponentially many times. Storing results in a table means each value is computed once, so the call tree collapses from 2^n nodes to n.' : 'For each element x, the program only needs to know whether k - x was already seen. A hash set answers that in O(1) expected time, so the inner loop over j disappears.',
      comparison: [{ label: 'Time', before: analysis.complexity.time, after: 'O(n)' }, { label: 'Space', before: analysis.complexity.space, after: 'O(n)' }, { label: fib ? 'Runtime at n=45' : 'Runtime at n=50000', before: fib ? '1.84 s' : '412.6 ms', after: fib ? '0.04 ms' : '3.1 ms' }],
      changes: fib ? ['added a memo table vector<long long> memo(n + 1, -1)', 'replaced the two direct recursive calls with a memoized helper', 'kept the base case n < 2 unchanged'] : ['loop over indices replaced with range-for', 'removed nested loop over j (lines 6-8)', 'added unordered_set<int> seen', 'pair comparison replaced with complement lookup'],
      tradeoff: fib ? 'Space rises from O(n) stack only to O(n) stack plus an O(n) table.' : 'Space rises from O(1) to O(n) for the hash set.',
      verification: '248 generated inputs compared against the reference solution: 0 mismatches. Edge cases run: empty, single element, all equal, sorted ascending, sorted descending, maximum values.',
      speedup: fib ? 46000 : 133.1,
    },
    success: true, error: '',
  };
}

export function trainHistory(req: TrainRequest, upto: number): EpochMetrics[] {
  const out: EpochMetrics[] = [];
  for (let e = 1; e <= Math.min(upto, req.epochs); e++) {
    const t = e / req.epochs;
    out.push({ epoch: e, train_loss: +(1.9 * Math.exp(-4 * t) + 0.08 + Math.sin(e) * 0.01).toFixed(4), val_loss: +(1.95 * Math.exp(-3.4 * t) + 0.2 + Math.cos(e) * 0.015).toFixed(4), val_accuracy: +(0.9 - 0.8 * Math.exp(-4.5 * t) + Math.sin(e * 1.3) * 0.008).toFixed(4) });
  }
  return out;
}

function view(r: Rec): Job {
  const { job } = r;
  if (job.status === 'cancelled' || job.status === 'done') return job;
  const elapsed = Date.now() - r.started;
  if (elapsed < 500) return { ...job, status: 'queued', progress: 0, stage: 'Queued' };
  const p = Math.min(100, Math.round((elapsed / r.duration) * 100));
  if (p < 100) {
    const stage = job.type === 'train' ? `Epoch ${mockEpochs(job.id).length} of ${r.train!.epochs}` : PIPELINE[PIPELINE.findIndex((s) => p <= s.at)].detail;
    return { ...job, status: 'running', progress: p, stage };
  }
  let result: Job['result'];
  if (job.type === 'train') {
    const history = trainHistory(r.train!, r.train!.epochs);
    const last = history[history.length - 1];
    const version = `v${models.length + 1}-${new Date().toISOString().slice(0, 10).replace(/-/g, '')}`;
    result = { version, accuracy: last.val_accuracy, loss: last.val_loss, epochs: history.length, dataset_size: 2840, history } as TrainResult;
    if (!r.modelAdded) { r.modelAdded = true; models = [...models, { id: models.length + 1, version, accuracy: last.val_accuracy, loss: last.val_loss, epochs: history.length, dataset_size: 2840, trained_at: new Date().toISOString(), is_active: false }]; }
  } else result = job.type === 'optimize' ? optimizeFor(job.input_code) : analysisFor(job.input_code);
  r.job = { ...job, status: 'done', progress: 100, stage: 'Done', result, finished_at: new Date().toISOString() };
  return r.job;
}

export function mockEpochs(id: number): EpochMetrics[] {
  const r = recs.find((x) => x.job.id === id);
  if (!r || !r.train) return [];
  const done = Math.floor(Math.max(0, Date.now() - r.started - 500) / ((r.duration - 500) / r.train.epochs));
  return trainHistory(r.train, done);
}

function seed() {
  const mk = (type: Job['type'], code: string, ago: number, pid: string | null): void => {
    const job: Job = { id: seq++, type, status: 'queued', problem_id: pid, input_code: code, progress: 0, stage: '', error: null, created_at: new Date(Date.now() - ago).toISOString(), finished_at: null };
    recs.push({ job, started: Date.now() - 60000, duration: 1000 });
  };
  mk('analyze', 'for (;;) { for (;;) {} }', 3600e3 * 5, 'pair_sum');
  mk('optimize', 'for (;;) { for (;;) {} }', 3600e3 * 4.9, 'pair_sum');
  mk('analyze', 'int mid = 0;', 86400e3 * 2, 'search');
  view(recs[0]); view(recs[1]); view(recs[2]);
}
seed();

export async function mockHandle(method: string, fullPath: string, body: any): Promise<unknown> {
  await wait();
  const path = fullPath.split('?')[0];
  if (path.endsWith('/auth/login') || path.endsWith('/auth/signup')) return { token: 'mock-token', user: { id: 1, username: body.username } };
  if (path.endsWith('/auth/me')) return { id: 1, username: 'student' };
  if (path.endsWith('/auth/logout')) return undefined;
  if (path.endsWith('/problems')) return PROBLEMS;
  if (path.endsWith('/execute')) {
    await wait(500);
    if (/syntax_error|;;;/.test(body.code)) return { success: false, compile_error: "main.cpp:3:5: error: expected ';' before '}' token", stdout: '', stderr: '', exit_code: 1, time_ms: 0, memory_kb: 0, timed_out: false };
    return { success: true, compile_error: '', stdout: body.stdin ? `echo: ${body.stdin}\n` : 'program finished with no output\n', stderr: '', exit_code: 0, time_ms: 12.4, memory_kb: 3120, timed_out: false };
  }
  if (path.endsWith('/models/train')) {
    const train = body as TrainRequest;
    const job: Job = { id: seq++, type: 'train', status: 'queued', problem_id: null, input_code: '', progress: 0, stage: 'Queued', error: null, created_at: new Date().toISOString(), finished_at: null };
    recs.push({ job, started: Date.now(), duration: 500 + train.epochs * 450, train });
    return { job_id: job.id };
  }
  if (path.endsWith('/models') && method === 'GET') return models;
  const act = path.match(/\/models\/(\d+)\/activate$/);
  if (act) { models = models.map((m) => ({ ...m, is_active: m.id === Number(act[1]) })); return undefined; }
  if (path.endsWith('/jobs') && method === 'POST') {
    const job: Job = { id: seq++, type: body.type, status: 'queued', problem_id: body.problem.problem_id || null, problem: body.problem, input_code: body.code, progress: 0, stage: 'Queued', error: null, created_at: new Date().toISOString(), finished_at: null };
    recs.push({ job, started: Date.now(), duration: body.type === 'optimize' ? 6500 : 4500 });
    return { job_id: job.id };
  }
  if (path.endsWith('/jobs')) return [...recs].reverse().map((r) => { const { result: _r, ...j } = view(r); return j as Job; });
  const cancel = path.match(/\/jobs\/(\d+)\/cancel$/);
  if (cancel) { const r = recs.find((x) => x.job.id === Number(cancel[1])); if (r && r.job.status !== 'done') r.job = { ...view(r), status: 'cancelled', stage: 'Cancelled', finished_at: new Date().toISOString() }; return undefined; }
  const one = path.match(/\/jobs\/(\d+)$/);
  if (one) { const r = recs.find((x) => x.job.id === Number(one[1])); if (!r) throw Object.assign(new Error('Job not found'), { status: 404 }); return view(r); }
  throw new Error(`Mock: no route for ${method} ${path}`);
}

export function mockSubscribe(jobId: number, onEvent: (e: WsEvent) => void, onState: (c: boolean) => void): () => void {
  onState(true);
  let sent = 0;
  const t = window.setInterval(async () => {
    const r = recs.find((x) => x.job.id === jobId);
    if (!r) return;
    const j = view(r);
    onEvent({ type: 'progress', percent: j.progress, stage: j.stage });
    for (const e of mockEpochs(jobId).slice(sent)) { onEvent({ type: 'epoch', ...e }); sent++; }
    if (j.status === 'done' || j.status === 'cancelled' || j.status === 'failed') { onEvent({ type: 'done' }); window.clearInterval(t); }
  }, 350);
  return () => window.clearInterval(t);
}
