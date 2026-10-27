import clsx from 'clsx';
import { Search } from 'lucide-react';
import { useEffect, useState } from 'react';
import { api } from '../../api/client';
import { fmtN } from '../../lib/format';
import type { Problem } from '../../types/api';
import { Badge, ErrorBox, Loading } from '../common/ui';

export default function ProblemPicker({ selectedId, onSelect, initialId }: { selectedId: string; onSelect: (p: Problem) => void; initialId?: string }) {
  const [items, setItems] = useState<Problem[] | null>(null);
  const [err, setErr] = useState('');
  const [q, setQ] = useState('');
  useEffect(() => { api.problems.list().then(setItems).catch((e) => setErr((e as Error).message)); }, []);
  useEffect(() => { if (items && initialId && !selectedId) { const p = items.find((x) => x.id === initialId); if (p) onSelect(p); } }, [items, initialId, selectedId, onSelect]);

  if (err) return <ErrorBox title="Could not load the problem catalog">{err}</ErrorBox>;
  if (!items) return <Loading label="Loading problems" />;
  const shown = items.filter((p) => (p.title + p.operation).toLowerCase().includes(q.toLowerCase()));
  return (
    <div>
      <div className="relative mb-3">
        <Search className="pointer-events-none absolute left-3 top-2.5 h-4 w-4 text-mute" />
        <input className="field !pl-9" placeholder="Search problems" value={q} onChange={(e) => setQ(e.target.value)} aria-label="Search problems" />
      </div>
      <div className="space-y-2">
        {shown.map((p) => (
          <button key={p.id} onClick={() => onSelect(p)} aria-pressed={p.id === selectedId}
            className={clsx('w-full rounded-lg border p-3 text-left transition-colors', p.id === selectedId ? 'border-accent bg-accent/10' : 'border-line hover:border-accent/50')}>
            <div className="flex items-center justify-between gap-2"><span className="font-medium">{p.title}</span><Badge tone="ok">{p.optimal_time}</Badge></div>
            {p.description && <p className="mt-1 text-sm text-mute">{p.description}</p>}
            <p className="mt-1.5 text-xs text-mute">Input {p.input_type}, output {p.output_type}, up to n = {fmtN(p.max_n)}</p>
          </button>
        ))}
        {shown.length === 0 && <p className="py-4 text-center text-sm text-mute">No problem matches "{q}". Switch to Custom to describe your own.</p>}
      </div>
    </div>
  );
}
