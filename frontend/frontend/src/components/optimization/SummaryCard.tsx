import { Zap } from 'lucide-react';
import type { OptimizationSummary } from '../../types/api';
import { Card } from '../common/ui';

const fmtSpeed = (x: number) => (x >= 100 ? `${Math.round(x).toLocaleString('en-US')}x` : `${x.toFixed(1)}x`);

export default function SummaryCard({ s, verification }: { s: OptimizationSummary; verification: React.ReactNode }) {
  return (
    <Card className="border-accent/40">
      <div className="flex flex-wrap items-start justify-between gap-6">
        <div className="max-w-2xl">
          <div className="mb-3">{verification}</div>
          <h2 className="text-2xl font-bold">{s.headline}</h2>
          <p className="mt-2 text-mute">{s.explanation}</p>
        </div>
        {s.speedup > 0 && (
          <div className="rounded-xl bg-accent/10 px-6 py-4 text-center">
            <Zap className="mx-auto mb-1 h-5 w-5 text-accent" />
            <p className="font-display text-4xl font-bold tabular-nums text-accent">{fmtSpeed(s.speedup)}</p>
            <p className="text-sm text-mute">measured speedup</p>
          </div>
        )}
      </div>
      {s.tradeoff && <p className="mt-5 rounded-lg bg-warn/10 p-3 text-sm"><span className="font-medium text-warn">Trade-off. </span>{s.tradeoff}</p>}
      {s.verification && <p className="mt-3 text-sm text-mute"><span className="font-medium text-ink">How it was checked. </span>{s.verification}</p>}
    </Card>
  );
}
