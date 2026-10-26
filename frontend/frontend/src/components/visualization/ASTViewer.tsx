import { ChevronRight } from 'lucide-react';
import { useMemo, useState } from 'react';
import { Badge, Button } from '../common/ui';
import type { Tone } from '../../lib/format';

interface AstNode { type: string; label?: string; line?: number; children?: AstNode[] }
const TONES: Record<string, Tone> = { Function: 'accent', Loop: 'warn', Branch: 'warn', Call: 'ok', Return: 'neutral' };

function Node({ n, depth, open }: { n: AstNode; depth: number; open: boolean | null }) {
  const [local, setLocal] = useState(depth < 3);
  const expanded = open ?? local;
  const kids = n.children ?? [];
  return (
    <li>
      <div className="flex items-center gap-2 py-1">
        <button disabled={!kids.length} onClick={() => setLocal(!expanded)} aria-label={expanded ? 'Collapse' : 'Expand'} className="h-5 w-5 text-mute disabled:opacity-0">
          <ChevronRight className={`h-4 w-4 transition-transform ${expanded ? 'rotate-90' : ''}`} />
        </button>
        <Badge tone={TONES[n.type] ?? 'neutral'}>{n.type}</Badge>
        {n.label && <span className="font-mono text-sm">{n.label}</span>}
        {n.line !== undefined && <span className="text-xs text-mute">line {n.line}</span>}
      </div>
      {expanded && kids.length > 0 && <ul className="ml-2.5 border-l border-line pl-4">{kids.map((k, i) => <Node key={i} n={k} depth={depth + 1} open={open} />)}</ul>}
    </li>
  );
}

export default function ASTViewer({ json }: { json: string }) {
  const [open, setOpen] = useState<boolean | null>(null);
  const [rev, setRev] = useState(0);
  const tree = useMemo<AstNode | null>(() => { try { return JSON.parse(json) as AstNode; } catch { return null; } }, [json]);
  if (!tree) return <p className="text-mute">The AST could not be read. Raw output:</p>;
  return (
    <div>
      <div className="mb-3 flex gap-2">
        <Button size="sm" variant="secondary" onClick={() => { setOpen(true); setRev(rev + 1); }}>Expand all</Button>
        <Button size="sm" variant="secondary" onClick={() => { setOpen(false); setRev(rev + 1); }}>Collapse all</Button>
      </div>
      <ul key={rev}><Node n={tree} depth={0} open={open} /></ul>
    </div>
  );
}
