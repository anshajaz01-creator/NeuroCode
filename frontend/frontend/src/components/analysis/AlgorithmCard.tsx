import { Info } from 'lucide-react';
import { fmtPct } from '../../lib/format';
import type { AlgorithmGuess } from '../../types/api';
import { Card } from '../common/ui';

export const LOW_CONFIDENCE = 0.5;

export default function AlgorithmCard({ algorithms }: { algorithms: AlgorithmGuess[] }) {
  const top = algorithms[0];
  const low = !top || top.probability < LOW_CONFIDENCE;
  return (
    <Card title="Detected algorithm" subtitle="Model prediction, top three. Advisory only.">
      {algorithms.length === 0 ? <p className="text-mute">The model returned no prediction for this code.</p> : (
        <ul className="space-y-4">
          {algorithms.map((a, i) => (
            <li key={a.label}>
              <div className="mb-1.5 flex items-baseline justify-between"><span className={i === 0 ? 'font-medium' : 'text-mute'}>{a.label}</span><span className="tabular-nums text-sm text-mute">{fmtPct(a.probability, 1)}</span></div>
              <div className="h-2 overflow-hidden rounded-full bg-raised"><div className={i === 0 ? 'h-full bg-accent' : 'h-full bg-mute/50'} style={{ width: `${a.probability * 100}%` }} /></div>
            </li>
          ))}
        </ul>
      )}
      {low && (
        <p className="mt-4 flex gap-2 rounded-lg bg-warn/10 p-3 text-sm text-warn"><Info className="mt-0.5 h-4 w-4 shrink-0" />
          Low confidence. Treat the complexity result below as the primary finding.</p>
      )}
    </Card>
  );
}
