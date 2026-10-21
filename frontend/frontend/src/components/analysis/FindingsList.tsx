import { AlertOctagon, AlertTriangle, CheckCircle2, Info } from 'lucide-react';
import { useState } from 'react';
import type { Finding, Severity } from '../../types/api';
import { Badge, Card, Segmented } from '../common/ui';
import type { Tone } from '../../lib/format';

const META: Record<Severity, { tone: Tone; icon: typeof Info; label: string }> = {
  high: { tone: 'bad', icon: AlertOctagon, label: 'High' },
  medium: { tone: 'warn', icon: AlertTriangle, label: 'Medium' },
  low: { tone: 'neutral', icon: Info, label: 'Low' },
};

export default function FindingsList({ findings, onJump }: { findings: Finding[]; onJump?: (line: number) => void }) {
  const [filter, setFilter] = useState<'all' | Severity>('all');
  const shown = findings.filter((f) => filter === 'all' || f.severity === filter);
  return (
    <Card title="Static findings" subtitle={`${findings.length} found by checks over the AST and control flow graph`}
      action={findings.length > 0 ? <Segmented value={filter} onChange={setFilter} label="Filter by severity" options={[{ value: 'all', label: 'All' }, { value: 'high', label: 'High' }, { value: 'medium', label: 'Medium' }, { value: 'low', label: 'Low' }]} /> : undefined}>
      {findings.length === 0 ? (
        <p className="flex items-center gap-2 text-ok"><CheckCircle2 className="h-5 w-5" />No findings. The static checks found nothing to report.</p>
      ) : shown.length === 0 ? <p className="text-mute">No {filter} severity findings.</p> : (
        <ul className="divide-y divide-line">
          {shown.map((f, i) => {
            const M = META[f.severity];
            return (
              <li key={i} className="flex items-start gap-3 py-3 first:pt-0 last:pb-0">
                <M.icon className={`mt-0.5 h-5 w-5 shrink-0 ${f.severity === 'high' ? 'text-bad' : f.severity === 'medium' ? 'text-warn' : 'text-mute'}`} />
                <div className="flex-1"><p>{f.message}</p><p className="mt-1 flex items-center gap-2 text-xs text-mute"><Badge tone={M.tone}>{M.label}</Badge><span className="font-mono">{f.type}</span></p></div>
                <button onClick={() => onJump?.(f.line)} className="rounded-md px-2 py-1 font-mono text-xs text-accent hover:bg-accent/10">line {f.line}</button>
              </li>
            );
          })}
        </ul>
      )}
    </Card>
  );
}
