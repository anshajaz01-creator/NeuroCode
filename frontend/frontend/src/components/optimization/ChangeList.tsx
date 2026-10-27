import { Card } from '../common/ui';

export default function ChangeList({ changes }: { changes: string[] }) {
  return (
    <Card title="What changed" subtitle="Each edit, found by comparing the original and generated syntax trees">
      <ol className="space-y-3">
        {changes.map((c, i) => (
          <li key={i} className="flex gap-3"><span className="flex h-6 w-6 shrink-0 items-center justify-center rounded-full bg-accent/15 text-xs font-semibold text-accent">{i + 1}</span><span>{c}</span></li>
        ))}
      </ol>
    </Card>
  );
}
