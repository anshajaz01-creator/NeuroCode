import clsx from 'clsx';
import { Check } from 'lucide-react';
import { PIPELINE, stageIndex } from '../../lib/pipeline';
import { ProgressBar } from '../common/ui';

export default function PipelineProgress({ percent, stage, status }: { percent: number; stage: string; status: string }) {
  const current = status === 'queued' ? -1 : stageIndex(percent);
  return (
    <div className="rounded-xl border border-line bg-panel p-6">
      <div className="mb-6 flex items-end justify-between gap-4">
        <div>
          <p className="font-display text-4xl font-bold tabular-nums">{percent}%</p>
          <p className="mt-1 text-mute">{status === 'queued' ? 'Waiting for a worker' : stage || 'Working'}</p>
        </div>
      </div>
      <ProgressBar percent={percent} className="mb-6" />
      <ol className="grid grid-cols-3 gap-3 sm:grid-cols-5 xl:grid-cols-9">
        {PIPELINE.map((s, i) => {
          const done = i < current || percent >= 100;
          const active = i === current && percent < 100;
          return (
            <li key={s.label} className="flex flex-col items-center gap-2 text-center">
              <span className={clsx('flex h-9 w-9 items-center justify-center rounded-full border text-sm font-semibold transition-colors',
                done ? 'border-accent bg-accent text-bg' : active ? 'animate-ring border-accent text-accent' : 'border-line text-mute')}>
                {done ? <Check className="h-4 w-4" /> : i + 1}
              </span>
              <span className={clsx('text-xs font-medium', done || active ? 'text-ink' : 'text-mute')}>{s.label}</span>
            </li>
          );
        })}
      </ol>
    </div>
  );
}
