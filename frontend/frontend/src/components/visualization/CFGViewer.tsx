import { Minus, Plus } from 'lucide-react';
import { useMemo, useState } from 'react';
import { Button } from '../common/ui';

interface CNode { id: string | number; label: string; kind?: string; line?: number }
interface CEdge { from: string | number; to: string | number; label?: string }
const W = 172, H = 54, GX = 36, GY = 60;
const STROKE: Record<string, string> = { entry: 'stroke-ok', exit: 'stroke-ok', loop: 'stroke-accent', branch: 'stroke-warn' };

export default function CFGViewer({ json }: { json: string }) {
  const [zoom, setZoom] = useState(1);
  const g = useMemo(() => {
    let cfg: { nodes: CNode[]; edges: CEdge[] };
    try { cfg = JSON.parse(json); } catch { return null; }
    if (!cfg.nodes?.length) return null;
    const ids = cfg.nodes.map((n) => String(n.id));
    const depth = new Map<string, number>([[ids[0], 0]]);
    const queue = [ids[0]];
    while (queue.length) {
      const c = queue.shift()!;
      for (const e of cfg.edges) if (String(e.from) === c && !depth.has(String(e.to))) { depth.set(String(e.to), depth.get(c)! + 1); queue.push(String(e.to)); }
    }
    ids.forEach((i) => { if (!depth.has(i)) depth.set(i, 0); });
    const layers = new Map<number, string[]>();
    ids.forEach((i) => layers.set(depth.get(i)!, [...(layers.get(depth.get(i)!) ?? []), i]));
    const maxCols = Math.max(...[...layers.values()].map((l) => l.length));
    const width = maxCols * (W + GX) + GX;
    const pos = new Map<string, { x: number; y: number }>();
    layers.forEach((l, d) => l.forEach((id, i) => pos.set(id, { x: (width - l.length * (W + GX)) / 2 + GX / 2 + i * (W + GX), y: d * (H + GY) + 20 })));
    return { cfg, pos, depth, width, height: (Math.max(...layers.keys()) + 1) * (H + GY) + 20 };
  }, [json]);
  if (!g) return <p className="text-mute">The control flow graph could not be read.</p>;

  return (
    <div>
      <div className="mb-3 flex items-center gap-2">
        <Button size="sm" variant="secondary" aria-label="Zoom out" onClick={() => setZoom((z) => Math.max(0.5, z - 0.15))}><Minus className="h-4 w-4" /></Button>
        <span className="w-12 text-center text-sm tabular-nums text-mute">{Math.round(zoom * 100)}%</span>
        <Button size="sm" variant="secondary" aria-label="Zoom in" onClick={() => setZoom((z) => Math.min(2, z + 0.15))}><Plus className="h-4 w-4" /></Button>
        <span className="ml-4 flex items-center gap-4 text-xs text-mute"><span className="flex items-center gap-1.5"><i className="inline-block h-0.5 w-5 bg-mute" />forward edge</span><span className="flex items-center gap-1.5"><i className="inline-block h-0.5 w-5 border-t-2 border-dashed border-warn" />back edge (loop)</span></span>
      </div>
      <div className="overflow-auto rounded-lg border border-line bg-raised/40" style={{ maxHeight: 560 }}>
        <svg width={g.width * zoom} height={g.height * zoom} viewBox={`0 0 ${g.width} ${g.height}`} role="img" aria-label="Control flow graph">
          <defs><marker id="arr" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto-start-reverse"><path d="M0 0L10 5L0 10z" fill="rgb(var(--mute))" /></marker></defs>
          {g.cfg.edges.map((e, i) => {
            const a = g.pos.get(String(e.from)), b = g.pos.get(String(e.to));
            if (!a || !b) return null;
            const back = g.depth.get(String(e.to))! <= g.depth.get(String(e.from))!;
            const sx = a.x + W / 2, sy = a.y + H, tx = b.x + W / 2, ty = b.y;
            const d = back ? `M${a.x + W} ${a.y + H / 2} C${a.x + W + 90} ${a.y + H / 2} ${b.x + W + 90} ${b.y + H / 2} ${b.x + W} ${b.y + H / 2}` : `M${sx} ${sy} C${sx} ${sy + 30} ${tx} ${ty - 30} ${tx} ${ty}`;
            return (
              <g key={i}>
                <path d={d} fill="none" strokeWidth={1.6} strokeDasharray={back ? '5 4' : undefined} markerEnd="url(#arr)" stroke={back ? 'rgb(var(--warn))' : 'rgb(var(--mute))'} />
                {e.label && <text x={back ? a.x + W + 40 : (sx + tx) / 2 + 6} y={back ? a.y + H / 2 - 6 : (sy + ty) / 2} className="fill-mute" fontSize={11}>{e.label}</text>}
              </g>
            );
          })}
          {g.cfg.nodes.map((n) => {
            const p = g.pos.get(String(n.id))!;
            return (
              <g key={String(n.id)} transform={`translate(${p.x} ${p.y})`}>
                <rect width={W} height={H} rx={10} strokeWidth={1.8} className={`fill-panel ${STROKE[n.kind ?? ''] ?? 'stroke-line'}`} />
                <text x={W / 2} y={n.line ? H / 2 - 2 : H / 2 + 4} textAnchor="middle" className="fill-ink" fontSize={13} fontFamily="JetBrains Mono, monospace">{n.label}</text>
                {n.line !== undefined && <text x={W / 2} y={H / 2 + 14} textAnchor="middle" className="fill-mute" fontSize={10}>line {n.line}</text>}
              </g>
            );
          })}
        </svg>
      </div>
    </div>
  );
}
