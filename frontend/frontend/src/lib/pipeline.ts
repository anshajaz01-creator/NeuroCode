// The nine engine steps from architecture.md section 3, with their progress thresholds.
export const PIPELINE = [
  { at: 10, label: 'Parse', detail: 'libclang builds the Clang AST' },
  { at: 20, label: 'Simplify', detail: 'Reduced to the internal AST' },
  { at: 30, label: 'Control flow', detail: 'Basic blocks and edges' },
  { at: 45, label: 'Complexity', detail: 'Time and space derivation' },
  { at: 55, label: 'Features', detail: 'Feature vector for the model' },
  { at: 65, label: 'Predict', detail: 'Ranked algorithm labels' },
  { at: 75, label: 'Static checks', detail: 'Findings over the AST and CFG' },
  { at: 90, label: 'Verify', detail: 'Generated tests against the reference' },
  { at: 100, label: 'Optimize', detail: 'Candidate transformation' },
] as const;

export function stageIndex(percent: number): number {
  const i = PIPELINE.findIndex((s) => percent <= s.at);
  return i === -1 ? PIPELINE.length - 1 : i;
}
