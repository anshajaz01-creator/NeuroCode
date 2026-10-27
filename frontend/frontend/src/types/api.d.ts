// Hand-mirrored from docs/api-spec.md and backend/src/engine/IEngine.hpp.
// If the spec changes, change this file the same day.

export type JobType = 'analyze' | 'optimize' | 'train';
export type JobStatus = 'queued' | 'running' | 'done' | 'failed' | 'cancelled';
export type Severity = 'high' | 'medium' | 'low';

export interface User { id: number; username: string }
export interface AuthResponse { token: string; user: User }

export interface ProblemSpec {
  problem_id: string; // empty if custom
  input_type: string;
  output_type: string;
  operation: string;
  max_n: number;
}
export interface Problem {
  id: string; title: string; input_type: string; output_type: string;
  operation: string; max_n: number; optimal_time: string; description?: string;
}

export interface AlgorithmGuess { label: string; probability: number }
export interface Complexity { time: string; space: string; derivation: string[] }
export interface Finding { line: number; severity: Severity; type: string; message: string }
export interface Counterexample { input: string; expected_output: string; actual_output: string }
export interface BenchmarkResult { before_ms: number; after_ms: number; before_kb: number; after_kb: number; n_used: number }

export interface AnalysisResult {
  algorithms: AlgorithmGuess[];
  complexity: Complexity;
  findings: Finding[];
  counterexamples: Counterexample[];
  ast_json: string;
  cfg_json: string;
  optimization_available: boolean;
  success: boolean;
  error: string;
}
export interface SummaryRow { label: string; before: string; after: string }
export interface OptimizationSummary {
  headline: string; explanation: string; comparison: SummaryRow[]; changes: string[];
  tradeoff: string; verification: string; speedup: number;
}
export interface OptimizeResult {
  analysis: AnalysisResult;
  recommended_algorithm: string;
  recommended_complexity: string;
  optimized_code: string; // empty when verified === false
  summary: OptimizationSummary;
  verified: boolean;
  bench: BenchmarkResult;
  success: boolean;
  error: string;
}

export interface EpochMetrics { epoch: number; train_loss: number; val_loss: number; val_accuracy: number }
export interface TrainResult {
  version: string; accuracy: number; loss: number; epochs: number; dataset_size: number; history: EpochMetrics[];
}
export type JobResult = AnalysisResult | OptimizeResult | TrainResult;

export interface Job {
  id: number;
  type: JobType;
  status: JobStatus;
  problem_id: string | null;
  problem?: ProblemSpec | null;
  input_code: string;
  progress: number;
  stage: string;
  error: string | null;
  created_at: string;
  finished_at: string | null;
  result?: JobResult | null;
}
export interface CreateJobRequest { type: 'analyze' | 'optimize'; code: string; problem: ProblemSpec }

export interface ExecuteRequest { code: string; stdin: string }
export interface ExecuteResponse {
  success: boolean; compile_error: string; stdout: string; stderr: string;
  exit_code: number; time_ms: number; memory_kb: number; timed_out: boolean;
}

export interface ModelInfo {
  id: number; version: string; accuracy: number; loss: number; epochs: number;
  dataset_size: number; trained_at: string; is_active: boolean;
}
export interface TrainRequest { epochs: number; learning_rate: number; batch_size: number; early_stopping_patience: number }

// WebSocket /ws/jobs/{id}
export type WsEvent =
  | { type: 'progress'; percent: number; stage: string }
  | { type: 'epoch'; epoch: number; train_loss: number; val_loss: number; val_accuracy: number }
  | { type: 'done' }
  | { type: 'error'; message: string };
