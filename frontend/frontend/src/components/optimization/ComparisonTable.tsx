import { ArrowRight } from 'lucide-react';
import type { SummaryRow } from '../../types/api';
import { Card } from '../common/ui';

export default function ComparisonTable({ rows }: { rows: SummaryRow[] }) {
  return (
    <Card title="Before and after" pad={false}>
      <table className="w-full text-left text-sm">
        <thead><tr className="border-b border-line text-mute"><th className="px-5 py-2.5 font-medium">Measure</th><th className="px-5 py-2.5 font-medium">Original</th><th /><th className="px-5 py-2.5 font-medium">Optimized</th></tr></thead>
        <tbody>
          {rows.map((r) => (
            <tr key={r.label} className="border-b border-line last:border-0">
              <td className="px-5 py-3">{r.label}</td><td className="px-5 py-3 font-mono">{r.before}</td>
              <td className="text-mute"><ArrowRight className="h-4 w-4" /></td><td className="px-5 py-3 font-mono font-medium text-ok">{r.after}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </Card>
  );
}
