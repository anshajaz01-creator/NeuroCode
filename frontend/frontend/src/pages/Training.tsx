import { Play, XCircle } from 'lucide-react';
import { useCallback, useEffect, useState } from 'react';
import { api } from '../api/client';
import PipelineProgress from '../components/analysis/PipelineProgress';
import LiveChart from '../components/charts/LiveChart';
import { Badge, Button, Card, EmptyState, ErrorBox, Loading, PageHeader, ProgressBar, Segmented } from '../components/common/ui';
import { useJob } from '../hooks/useJob';
import { fmtN, fmtPct, isTerminal, relTime } from '../lib/format';
import type { ModelInfo, TrainRequest, TrainResult } from '../types/api';

const PRESETS: Record<string, TrainRequest> = {
  quick: { epochs: 30, learning_rate: 0.003, batch_size: 64, early_stopping_patience: 5 },
  balanced: { epochs: 80, learning_rate: 0.001, batch_size: 32, early_stopping_patience: 10 },
  thorough: { epochs: 200, learning_rate: 0.0005, batch_size: 32, early_stopping_patience: 20 },
};
const KEY = 'nc.trainJob';

export default function Training() {
  const [preset, setPreset] = useState<'quick' | 'balanced' | 'thorough' | 'custom'>('balanced');
  const [cfg, setCfg] = useState<TrainRequest>(PRESETS.balanced);
  const [jobId, setJobId] = useState<number | undefined>(() => Number(localStorage.getItem(KEY)) || undefined);
  const [starting, setStarting] = useState(false);
  const [err, setErr] = useState('');
  const [models, setModels] = useState<ModelInfo[] | null>(null);
  const { job, live } = useJob(jobId);

  const loadModels = useCallback(() => { api.models.list().then(setModels).catch((e) => setErr((e as Error).message)); }, []);
  useEffect(loadModels, [loadModels]);
  useEffect(() => { if (job?.status === 'done') loadModels(); }, [job?.status, loadModels]);

  const pick = (p: typeof preset) => { setPreset(p); if (p !== 'custom') setCfg(PRESETS[p]); };
  const set = <K extends keyof TrainRequest>(k: K, v: TrainRequest[K]) => { setPreset('custom'); setCfg({ ...cfg, [k]: v }); };

  const start = async () => {
    setErr(''); setStarting(true);
    try { const { job_id } = await api.models.train(cfg); localStorage.setItem(KEY, String(job_id)); setJobId(job_id); }
    catch (e) { setErr((e as Error).message); } finally { setStarting(false); }
  };
  const activate = async (id: number) => { await api.models.activate(id); loadModels(); };

  const running = !!job && !isTerminal(job.status);
  const result = job?.status === 'done' ? (job.result as TrainResult) : undefined;
  const data = result?.history ?? live.epochs;
  const last = data[data.length - 1];

  return (
    <>
      <PageHeader title="Model training" description="Train the algorithm classifier and watch the loss fall in real time. The new model stays inactive until you activate it." />
      <div className="grid gap-6 xl:grid-cols-[360px_minmax(0,1fr)]">
        <Card title="Training settings" subtitle="Defaults match the architecture: Adam, batch 32, early stopping.">
          <div className="space-y-5">
            <Segmented value={preset} onChange={pick} label="Preset" options={[{ value: 'quick', label: 'Quick' }, { value: 'balanced', label: 'Balanced' }, { value: 'thorough', label: 'Thorough' }, { value: 'custom', label: 'Custom' }]} />
            <div><label className="label" htmlFor="ep">Epochs: {cfg.epochs}</label><input id="ep" type="range" min={10} max={300} step={5} value={cfg.epochs} onChange={(e) => set('epochs', Number(e.target.value))} className="w-full accent-[rgb(var(--accent))]" />
              <p className="hint">Maximum. Early stopping can end the run sooner.</p></div>
            <div><label className="label" htmlFor="lr">Learning rate</label>
              <select id="lr" className="field" value={cfg.learning_rate} onChange={(e) => set('learning_rate', Number(e.target.value))}>{[0.0001, 0.0005, 0.001, 0.003, 0.01].map((v) => <option key={v} value={v}>{v}</option>)}</select></div>
            <div><label className="label" htmlFor="bs">Batch size</label>
              <select id="bs" className="field" value={cfg.batch_size} onChange={(e) => set('batch_size', Number(e.target.value))}>{[16, 32, 64, 128].map((v) => <option key={v}>{v}</option>)}</select></div>
            <div><label className="label" htmlFor="pat">Early stopping patience</label>
              <input id="pat" type="number" min={1} max={50} className="field" value={cfg.early_stopping_patience} onChange={(e) => set('early_stopping_patience', Math.max(1, Number(e.target.value) || 1))} />
              <p className="hint">Stop after this many epochs without validation improvement.</p></div>
            {err && <ErrorBox title="Training request failed">{err}</ErrorBox>}
            <Button size="lg" className="w-full" icon={<Play className="h-5 w-5" />} loading={starting} disabled={running} onClick={() => void start()}>{running ? 'Training in progress' : 'Start training'}</Button>
            {running && <Button variant="danger" className="w-full" icon={<XCircle className="h-4 w-4" />} onClick={() => void api.jobs.cancel(job!.id)}>Cancel run</Button>}
          </div>
        </Card>

        <div className="space-y-6">
          {running && (live.epochs.length === 0 ? <PipelineProgress percent={0} stage="Preparing the dataset" status="queued" /> : (
            <Card><div className="mb-2 flex justify-between text-sm"><span>{job!.stage || `Epoch ${last?.epoch}`}</span><span className="tabular-nums text-mute">{live.percent || job!.progress}%</span></div><ProgressBar percent={live.percent || job!.progress} /></Card>
          ))}
          <Card title="Loss and accuracy" subtitle={result ? `Finished as ${result.version}` : 'Updates after every epoch'}>
            {data.length === 0 ? <EmptyState title="No run in progress">Start training to see the curves here.</EmptyState> : (
              <>
                <div className="mb-4 grid grid-cols-3 gap-3 text-sm">
                  {[['Epoch', String(last.epoch)], ['Validation loss', last.val_loss.toFixed(3)], ['Validation accuracy', fmtPct(last.val_accuracy, 1)]].map(([l, v]) => (
                    <div key={l} className="rounded-lg bg-raised px-4 py-3"><p className="text-mute">{l}</p><p className="font-display text-2xl font-bold tabular-nums">{v}</p></div>
                  ))}
                </div>
                <LiveChart data={data} />
              </>
            )}
          </Card>
          {job?.status === 'failed' && <ErrorBox title="Training failed">{job.error || 'The trainer reported an error without details.'}</ErrorBox>}

          <Card title="Saved models" pad={false}>
            {!models ? <Loading label="Loading models" /> : models.length === 0 ? <div className="p-5"><EmptyState title="No models yet">Train one to get started.</EmptyState></div> : (
              <div className="overflow-x-auto"><table className="w-full text-left text-sm">
                <thead><tr className="border-b border-line text-mute">{['Version', 'Accuracy', 'Loss', 'Epochs', 'Samples', 'Trained', ''].map((h) => <th key={h} className="px-5 py-3 font-medium">{h}</th>)}</tr></thead>
                <tbody>{[...models].reverse().map((m) => (
                  <tr key={m.id} className="border-b border-line last:border-0">
                    <td className="px-5 py-3 font-mono">{m.version}</td><td className="px-5 py-3 tabular-nums">{fmtPct(m.accuracy, 1)}</td><td className="px-5 py-3 tabular-nums">{m.loss.toFixed(3)}</td>
                    <td className="px-5 py-3 tabular-nums">{m.epochs}</td><td className="px-5 py-3 tabular-nums">{fmtN(m.dataset_size)}</td><td className="px-5 py-3 text-mute">{relTime(m.trained_at)}</td>
                    <td className="px-5 py-3 text-right">{m.is_active ? <Badge tone="ok">Active</Badge> : <Button size="sm" variant="secondary" onClick={() => void activate(m.id)}>Activate</Button>}</td>
                  </tr>))}</tbody>
              </table></div>
            )}
          </Card>
        </div>
      </div>
    </>
  );
}
