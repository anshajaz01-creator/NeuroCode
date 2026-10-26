import { ArrowLeft } from 'lucide-react';
import { useState } from 'react';
import { Link, useNavigate, useParams } from 'react-router-dom';
import PipelineProgress from '../components/analysis/PipelineProgress';
import { Badge, Button, Card, ErrorBox, Loading, PageHeader, Tabs } from '../components/common/ui';
import DiffViewer from '../components/editor/DiffViewer';
import OptimizedCodePanel from '../components/editor/OptimizedCodePanel';
import ChangeList from '../components/optimization/ChangeList';
import ComparisonTable from '../components/optimization/ComparisonTable';
import SummaryCard from '../components/optimization/SummaryCard';
import VerificationBadge from '../components/optimization/VerificationBadge';
import ComplexityGraph from '../components/visualization/ComplexityGraph';
import { useJob } from '../hooks/useJob';
import { fmtKb, fmtMs, fmtN, isTerminal, statusTone } from '../lib/format';
import type { OptimizeResult } from '../types/api';

type Tab = 'diff' | 'code' | 'bench' | 'growth';

export default function Optimization() {
  const id = Number(useParams().id);
  const nav = useNavigate();
  const { job, error, live, refresh } = useJob(id);
  const [tab, setTab] = useState<Tab>('diff');
  const r = job?.result as OptimizeResult | undefined;

  if (error && !job) return <ErrorBox title="Could not load this optimization" action={<Button size="sm" variant="secondary" onClick={() => void refresh()}>Try again</Button>}>{error}</ErrorBox>;
  if (!job) return <Loading label="Loading optimization" />;
  const running = !isTerminal(job.status);
  const edit = (code: string) => nav('/analyze', { state: { code } });

  return (
    <>
      <Link to="/history" className="mb-4 inline-flex items-center gap-1.5 text-sm text-mute hover:text-ink"><ArrowLeft className="h-4 w-4" />History</Link>
      <PageHeader title={`Optimization #${job.id}`} description="A faster version of your code, checked against the reference solution before it is shown."
        actions={<Badge tone={statusTone[job.status]} className="!px-3 !py-1.5 !text-sm">{job.status}</Badge>} />

      {running && <PipelineProgress percent={live.percent || job.progress} stage={live.stage || job.stage} status={job.status} />}
      {job.status === 'failed' && <ErrorBox title="The optimization failed">{job.error || r?.error || 'The engine reported an error without details.'}</ErrorBox>}
      {job.status === 'cancelled' && <ErrorBox title="This optimization was cancelled" />}

      {job.status === 'done' && r && !r.success && <ErrorBox title="The engine could not optimize this code">{r.error}</ErrorBox>}
      {job.status === 'done' && r?.success && !r.verified && (
        <Card title="No verified optimization" action={<VerificationBadge verified={false} />}>
          <p className="max-w-2xl text-mute">NeuroCode never shows rewritten code it could not prove equal to your original on its tests. Either no transformation applies, or the candidate disagreed with the reference. Your analysis is unchanged.</p>
          <div className="mt-4 flex gap-2"><Button variant="secondary" onClick={() => edit(job.input_code)}>Edit code</Button></div>
        </Card>
      )}

      {job.status === 'done' && r?.success && r.verified && (
        <div className="space-y-6">
          <SummaryCard s={r.summary} verification={<VerificationBadge verified />} />
          <div className="grid gap-6 lg:grid-cols-2"><ComparisonTable rows={r.summary.comparison} /><ChangeList changes={r.summary.changes} /></div>
          <Tabs value={tab} onChange={setTab} tabs={[{ value: 'diff', label: 'Code diff' }, { value: 'code', label: 'Optimized code' }, { value: 'bench', label: 'Benchmark' }, { value: 'growth', label: 'Growth curves' }]} />
          {tab === 'diff' && <Card><DiffViewer original={job.input_code} modified={r.optimized_code} /></Card>}
          {tab === 'code' && <Card><OptimizedCodePanel code={r.optimized_code} onUse={() => edit(r.optimized_code)} /></Card>}
          {tab === 'bench' && (
            <Card title="Measured on one machine, in one run" subtitle={`Input size n = ${fmtN(r.bench.n_used)}`}>
              <div className="grid gap-4 sm:grid-cols-2">
                {[{ l: 'Runtime', b: fmtMs(r.bench.before_ms), a: fmtMs(r.bench.after_ms) }, { l: 'Memory', b: fmtKb(r.bench.before_kb), a: fmtKb(r.bench.after_kb) }].map((m) => (
                  <div key={m.l} className="rounded-lg bg-raised p-4"><p className="text-sm text-mute">{m.l}</p>
                    <p className="mt-1 font-mono"><span className="text-mute">{m.b}</span> <span className="text-mute">to</span> <span className="text-xl font-medium text-ok">{m.a}</span></p></div>
                ))}
              </div>
              <p className="mt-4 text-sm text-mute">Speedup is the ratio of the two measured timings, never inferred from complexity classes.</p>
            </Card>
          )}
          {tab === 'growth' && <Card title="Before and after as n grows"><ComplexityGraph time={r.analysis.complexity.time} optimized={r.recommended_complexity} /></Card>}
        </div>
      )}
    </>
  );
}
