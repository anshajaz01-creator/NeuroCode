import type { ProblemSpec } from '../../types/api';

const INPUTS = ['int_array', 'string', 'graph', 'matrix', 'int'];
const OUTPUTS = ['bool', 'int', 'array', 'string'];
const OPS = ['pair_sum', 'search', 'sort', 'range_sum', 'scheduling', 'traversal', 'other'];
const SIZES = [1_000, 10_000, 100_000, 1_000_000];

export const BLANK_SPEC: ProblemSpec = { problem_id: '', input_type: 'int_array', output_type: 'bool', operation: 'pair_sum', max_n: 10_000 };

export default function ProblemForm({ value, onChange }: { value: ProblemSpec; onChange: (v: ProblemSpec) => void }) {
  const set = <K extends keyof ProblemSpec>(k: K, v: ProblemSpec[K]) => onChange({ ...value, [k]: v });
  return (
    <div className="space-y-4">
      <div><label className="label" htmlFor="op">Operation</label>
        <select id="op" className="field" value={value.operation} onChange={(e) => set('operation', e.target.value)}>{OPS.map((o) => <option key={o}>{o}</option>)}</select>
        <p className="hint">What the function is supposed to compute. This decides which optimizations apply.</p></div>
      <div className="grid grid-cols-2 gap-3">
        <div><label className="label" htmlFor="in">Input type</label>
          <select id="in" className="field" value={value.input_type} onChange={(e) => set('input_type', e.target.value)}>{INPUTS.map((o) => <option key={o}>{o}</option>)}</select></div>
        <div><label className="label" htmlFor="out">Output type</label>
          <select id="out" className="field" value={value.output_type} onChange={(e) => set('output_type', e.target.value)}>{OUTPUTS.map((o) => <option key={o}>{o}</option>)}</select></div>
      </div>
      <div><label className="label" htmlFor="maxn">Largest input size (n)</label>
        <input id="maxn" type="number" min={1} className="field" value={value.max_n} onChange={(e) => set('max_n', Math.max(1, Number(e.target.value) || 1))} />
        <div className="mt-2 flex flex-wrap gap-1.5">
          {SIZES.map((s) => (
            <button key={s} type="button" onClick={() => set('max_n', s)}
              className={`rounded-md border px-2 py-1 text-xs ${value.max_n === s ? 'border-accent text-accent' : 'border-line text-mute hover:text-ink'}`}>{s.toLocaleString('en-US')}</button>
          ))}
        </div>
        <p className="hint">Some optimizations only pay off above a size threshold.</p></div>
    </div>
  );
}
