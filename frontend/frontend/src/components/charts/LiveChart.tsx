import { CartesianGrid, Legend, Line, LineChart, ResponsiveContainer, Tooltip, XAxis, YAxis } from 'recharts';
import type { EpochMetrics } from '../../types/api';

export default function LiveChart({ data }: { data: EpochMetrics[] }) {
  return (
    <div style={{ height: 340 }} aria-label="Training loss and validation accuracy by epoch" role="img">
      <ResponsiveContainer>
        <LineChart data={data} margin={{ top: 8, right: 8, bottom: 8, left: 0 }}>
          <CartesianGrid stroke="rgb(var(--line))" strokeDasharray="3 3" />
          <XAxis dataKey="epoch" stroke="rgb(var(--mute))" tick={{ fontSize: 12 }} />
          <YAxis yAxisId="loss" stroke="rgb(var(--mute))" tick={{ fontSize: 12 }} />
          <YAxis yAxisId="acc" orientation="right" domain={[0, 1]} stroke="rgb(var(--mute))" tick={{ fontSize: 12 }} tickFormatter={(v: number) => `${Math.round(v * 100)}%`} />
          <Tooltip contentStyle={{ background: 'rgb(var(--panel))', border: '1px solid rgb(var(--line))', borderRadius: 8 }} />
          <Legend />
          <Line yAxisId="loss" dataKey="train_loss" name="Train loss" stroke="#7a89ff" dot={false} strokeWidth={2} isAnimationActive={false} />
          <Line yAxisId="loss" dataKey="val_loss" name="Validation loss" stroke="#f5b544" dot={false} strokeWidth={2} isAnimationActive={false} />
          <Line yAxisId="acc" dataKey="val_accuracy" name="Validation accuracy" stroke="#34d399" dot={false} strokeWidth={2} strokeDasharray="5 4" isAnimationActive={false} />
        </LineChart>
      </ResponsiveContainer>
    </div>
  );
}
