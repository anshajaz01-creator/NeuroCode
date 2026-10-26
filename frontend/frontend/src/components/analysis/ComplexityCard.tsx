import type { Complexity } from '../../types/api';
import { Badge, Card } from '../common/ui';

const Big = ({ label, value }: { label: string; value: string }) => (
  <div className="rounded-lg bg-raised px-4 py-3">
    <p className="text-sm text-mute">{label}</p>
    <p className="font-mono text-2xl font-medium">{value || 'unknown'}</p>
  </div>
);

export default function ComplexityCard({ complexity }: { complexity: Complexity }) {
  const unknown = !complexity.time || complexity.time === 'unknown';
  return (
    <Card title="Complexity" subtitle="Derived by rules, not predicted by the model." action={<Badge tone="ok">Deterministic</Badge>}>
      <div className="grid grid-cols-2 gap-3"><Big label="Time" value={complexity.time} /><Big label="Space" value={complexity.space} /></div>
      {unknown && <p className="mt-3 text-sm text-mute">The engine does not recognise this pattern, so it reports unknown instead of guessing.</p>}
      {complexity.derivation.length > 0 && (
        <div className="mt-5">
          <h3 className="mb-2 text-sm font-bold">How the engine got there</h3>
          <ol className="space-y-2">
            {complexity.derivation.map((d, i) => (
              <li key={i} className="flex gap-3 text-sm"><span className="flex h-5 w-5 shrink-0 items-center justify-center rounded-full bg-accent/15 text-xs font-semibold text-accent">{i + 1}</span><span>{d}</span></li>
            ))}
          </ol>
        </div>
      )}
    </Card>
  );
}
