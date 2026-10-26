import type { ReactNode } from 'react';
import { fmtPct } from '../../lib/format';
import type { AnalysisResult } from '../../types/api';

// The architecture doc mentions "the three defined metrics" without naming them.
// Using: model confidence, findings, counterexamples. Swap here if the group defined others.
const Metric = ({ label, value, note, tone }: { label: string; value: ReactNode; note: string; tone: string }) => (
  <div className="rounded-xl border border-line bg-panel p-5">
    <p className="text-sm text-mute">{label}</p>
    <p className={`mt-1 font-display text-3xl font-bold tabular-nums ${tone}`}>{value}</p>
    <p className="mt-1 text-sm text-mute">{note}</p>
  </div>
);

export default function MetricsBar({ r }: { r: AnalysisResult }) {
  const conf = r.algorithms[0]?.probability ?? 0;
  const high = r.findings.filter((f) => f.severity === 'high').length;
  return (
    <div className="grid gap-4 sm:grid-cols-3">
      <Metric label="Model confidence" value={fmtPct(conf)} note={r.algorithms[0]?.label ?? 'No prediction'} tone={conf >= 0.5 ? 'text-ink' : 'text-warn'} />
      <Metric label="Findings" value={r.findings.length} note={high ? `${high} high severity` : 'None high severity'} tone={high ? 'text-bad' : 'text-ink'} />
      <Metric label="Counterexamples" value={r.counterexamples.length} note={r.counterexamples.length ? 'Output differs from reference' : 'Matches the reference'} tone={r.counterexamples.length ? 'text-bad' : 'text-ok'} />
    </div>
  );
}
