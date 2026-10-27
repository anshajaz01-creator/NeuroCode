import { CartesianGrid, Legend, Line, LineChart, ResponsiveContainer, Tooltip, XAxis, YAxis } from 'recharts';

const CLASSES = [
  { key: 'o1', name: 'O(1)', color: '#34d399', f: () => 1 },
  { key: 'logn', name: 'O(log n)', color: '#22d3ee', f: (n: number) => Math.log2(n) },
  { key: 'n', name: 'O(n)', color: '#7a89ff', f: (n: number) => n },
  { key: 'nlogn', name: 'O(n log n)', color: '#c084fc', f: (n: number) => n * Math.log2(n) },
  { key: 'n2', name: 'O(n^2)', color: '#f5b544', f: (n: number) => n * n },
  { key: '2n', name: 'O(2^n)', color: '#f87171', f: (n: number) => 2 ** n },
];

export function classKey(t: string): string {
  const s = t.toLowerCase().replace(/[o()\s]/g, '');
  return s === '1' ? 'o1' : s === 'logn' ? 'logn' : s === 'n' ? 'n' : s === 'nlogn' ? 'nlogn' : s === 'n^2' ? 'n2' : s === '2^n' ? '2n' : '';
}

export default function ComplexityGraph({ time, optimized }: { time: string; optimized?: string }) {
  const hit = classKey(time), opt = optimized ? classKey(optimized) : '';
  const CAP = 300;
  const data = Array.from({ length: 20 }, (_, i) => {
    const n = i + 1;
    return { n, ...Object.fromEntries(CLASSES.map((c) => [c.key, Math.min(CAP, c.f(n))])) };
  });
  return (
    <div>
      <p className="mb-4 max-w-2xl text-sm text-mute">
        Shape of each growth class as n increases. Your code's class{hit ? '' : ' is unknown, so none is'} highlighted.
        {opt && ' The optimized class is shown in a dashed line.'} These are reference curves, not timings from your code.
      </p>
      <div style={{ height: 360 }}>
        <ResponsiveContainer>
          <LineChart data={data} margin={{ top: 8, right: 16, bottom: 8, left: 0 }}>
            <CartesianGrid stroke="rgb(var(--line))" strokeDasharray="3 3" />
            <XAxis dataKey="n" stroke="rgb(var(--mute))" tick={{ fontSize: 12 }} label={{ value: 'input size n', position: 'insideBottom', offset: -2, fill: 'rgb(var(--mute))', fontSize: 12 }} />
            <YAxis stroke="rgb(var(--mute))" tick={{ fontSize: 12 }} domain={[0, CAP]} />
            <Tooltip contentStyle={{ background: 'rgb(var(--panel))', border: '1px solid rgb(var(--line))', borderRadius: 8 }} />
            <Legend />
            {CLASSES.map((c) => (
              <Line key={c.key} dataKey={c.key} name={c.name} stroke={c.color} dot={false} isAnimationActive={false}
                strokeWidth={c.key === hit || c.key === opt ? 3.5 : 1.5} strokeOpacity={c.key === hit || c.key === opt ? 1 : 0.3} strokeDasharray={c.key === opt && c.key !== hit ? '6 4' : undefined} />
            ))}
          </LineChart>
        </ResponsiveContainer>
      </div>
    </div>
  );
}
