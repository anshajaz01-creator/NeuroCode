import { CheckCircle2 } from 'lucide-react';
import type { Counterexample } from '../../types/api';
import { Card } from '../common/ui';

const Row = ({ label, value, tone }: { label: string; value: string; tone?: string }) => (
  <div><p className="mb-1 text-xs text-mute">{label}</p><pre className={`overflow-x-auto rounded-md bg-raised px-3 py-2 font-mono text-sm ${tone ?? ''}`}>{value}</pre></div>
);

export default function CounterexampleCard({ items }: { items: Counterexample[] }) {
  return (
    <Card title="Counterexamples" subtitle="Inputs where your output differs from the reference solution">
      {items.length === 0 ? (
        <div>
          <p className="flex items-center gap-2 text-ok"><CheckCircle2 className="h-5 w-5" />No mismatches on the generated tests.</p>
          <p className="mt-2 text-sm text-mute">Testing finds bugs. It does not prove their absence.</p>
        </div>
      ) : (
        <ul className="space-y-5">
          {items.map((c, i) => (
            <li key={i} className="space-y-3 rounded-lg border border-bad/30 p-4">
              <Row label="Input" value={c.input} />
              <div className="grid gap-3 sm:grid-cols-2"><Row label="Expected" value={c.expected_output} tone="text-ok" /><Row label="Your code returned" value={c.actual_output} tone="text-bad" /></div>
            </li>
          ))}
        </ul>
      )}
    </Card>
  );
}
