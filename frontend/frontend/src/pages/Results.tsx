import { ArrowLeft, Sparkles, XCircle } from 'lucide-react';
import { useMemo, useState } from 'react';
import { Link, Navigate, useNavigate, useParams } from 'react-router-dom';
import { api } from '../api/client';
import AlgorithmCard from '../components/analysis/AlgorithmCard';
import ComplexityCard from '../components/analysis/ComplexityCard';
import CounterexampleCard from '../components/analysis/CounterexampleCard';
import FindingsList from '../components/analysis/FindingsList';
import MetricsBar from '../components/analysis/MetricsBar';
import PipelineProgress from '../components/analysis/PipelineProgress';
import { Badge, Button, Card, ErrorBox, Loading, PageHeader, Tabs } from '../components/common/ui';
import CodeEditor from '../components/editor/CodeEditor';
import ASTViewer from '../components/visualization/ASTViewer';
import CFGViewer from '../components/visualization/CFGViewer';
import ComplexityGraph from '../components/visualization/ComplexityGraph';
import { useJob } from '../hooks/useJob';
import { isTerminal, relTime, statusTone } from '../lib/format';
import type { AnalysisResult, ProblemSpec } from '../types/api';

type Tab = 'overview' | 'code' | 'structure' | 'growth';

export default function Results() {
  const id = Number(useParams().id);
  const nav = useNavigate();
  const { job, error, live, refresh } = useJob(id);
  const [tab, setTab] = useState<Tab>('overview');
  const [graph, setGraph] = useState<'ast' | 'cfg'>('cfg');
  const [starting, setStarting] = useState(false);
  const [actErr, setActErr] = useState('');
  const r = job?.result as AnalysisResult | undefined;
  const markers = useMemo(() => (r?.findings ?? []).map((f) => ({ line: f.line, message: f.message, severity: f.severity })), [r]);

  if (error && !job) return <ErrorBox title="Could not load this analysis" action={<Button size="sm" variant="secondary" onClick={() => void refresh()}>Try again</Button>}>{error}</ErrorBox>;
  if (!job) return <Loading label="Loading analysis" />;
  if (job.type === 'optimize') return <Navigate to={`/optimize/${job.id}`} replace />;
  if (job.type === 'train') return <Navigate to="/training" replace />;

  const optimize = async () => {
    setActErr(''); setStarting(true);
    const spec: ProblemSpec = job.problem ?? { problem_id: job.problem_id ?? '', input_type: 'int_array', output_type: 'bool', operation: 'other', max_n: 10000 };
    try { const { job_id } = await api.jobs.create({ type: 'optimize', code: job.input_code, problem: spec }); nav(`/optimize/${job_id}`); }
    catch (e) { setActErr((e as Error).message); setStarting(false); }
  };
  const cancel = async () => { await api.jobs.cancel(job.id); await refresh(); };
  const running = !isTerminal(job.status);

  return (
    <>
      <Link to="/analyze" className="mb-4 inline-flex items-center gap-1.5 text-sm text-mute hover:text-ink"><ArrowLeft className="h-4 w-4" />Back to editor</Link>
      <PageHeader title={`Analysis #${job.id}`} description={`Started ${relTime(job.created_at)}${job.problem_id ? ` for problem ${job.problem_id}` : ' with a custom problem'}.`}
        actions={<>
          <Badge tone={statusTone[job.status]} className="!px-3 !py-1.5 !text-sm">{job.status}</Badge>
          {running && <Button variant="danger" icon={<XCircle className="h-4 w-4" />} onClick={() => void cancel()}>Cancel</Button>}
          {r?.optimization_available && <Button icon={<Sparkles className="h-4 w-4" />} loading={starting} onClick={() => void optimize()}>Optimize this code</Button>}
          {job.status === 'done' && <Button variant="secondary" onClick={() => nav('/analyze', { state: { code: job.input_code } })}>Edit and re-run</Button>}
        </>} />
      {actErr && <div className="mb-4"><ErrorBox title="Could not start the optimization">{actErr}</ErrorBox></div>}

      {running && <PipelineProgress percent={live.percent || job.progress} stage={live.stage || job.stage} status={job.status} />}
      {job.status === 'failed' && <ErrorBox title="The analysis failed">{job.error || r?.error || 'The engine reported an error without details.'}</ErrorBox>}
      {job.status === 'cancelled' && <ErrorBox title="You cancelled this analysis" action={<Button size="sm" variant="secondary" onClick={() => nav('/analyze', { state: { code: job.input_code } })}>Edit and re-run</Button>} />}

      {job.status === 'done' && r && !r.success && <ErrorBox title="The engine could not analyze this code">{r.error}</ErrorBox>}
      {job.status === 'done' && r?.success && (
        <div className="space-y-6">
          <MetricsBar r={r} />
          {!r.optimization_available && <p className="rounded-lg border border-line bg-panel p-3 text-sm text-mute">No safe optimization applies to this code, so there is nothing to generate.</p>}
          <Tabs value={tab} onChange={setTab} tabs={[
            { value: 'overview', label: 'Overview' },
            { value: 'code', label: 'Code', badge: r.findings.length ? <Badge tone="warn">{r.findings.length}</Badge> : undefined },
            { value: 'structure', label: 'Structure' },
            { value: 'growth', label: 'Growth curves' },
          ]} />
          {tab === 'overview' && (
            <div className="grid gap-6 lg:grid-cols-2">
              <ComplexityCard complexity={r.complexity} />
              <AlgorithmCard algorithms={r.algorithms} />
              <FindingsList findings={r.findings} onJump={() => setTab('code')} />
              <CounterexampleCard items={r.counterexamples} />
            </div>
          )}
          {tab === 'code' && (
            <Card title="Your code" subtitle={r.findings.length ? 'Lines with findings are underlined. Hover to read them.' : 'No findings to mark.'}><CodeEditor value={job.input_code} readOnly markers={markers} height="480px" /></Card>
          )}
          {tab === 'structure' && (
            <Card title={graph === 'cfg' ? 'Control flow graph' : 'Syntax tree'} subtitle="The engine's internal view of your code"
              action={<div className="flex gap-1 rounded-lg border border-line bg-raised p-0.5">{(['cfg', 'ast'] as const).map((g) => <button key={g} onClick={() => setGraph(g)} aria-pressed={graph === g} className={`rounded-md px-3 py-1 text-sm ${graph === g ? 'bg-panel font-medium' : 'text-mute'}`}>{g.toUpperCase()}</button>)}</div>}>
              {graph === 'cfg' ? <CFGViewer json={r.cfg_json} /> : <ASTViewer json={r.ast_json} />}
            </Card>
          )}
          {tab === 'growth' && <Card title="How your complexity scales"><ComplexityGraph time={r.complexity.time} /></Card>}
        </div>
      )}
    </>
  );
}
