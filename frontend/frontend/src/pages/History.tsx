import { RefreshCw, Search } from 'lucide-react';
import { useCallback, useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import { api } from '../api/client';
import { Badge, Button, EmptyState, ErrorBox, Loading, PageHeader, Segmented } from '../components/common/ui';
import { jobHref, relTime, statusTone, typeLabel } from '../lib/format';
import type { Job, JobStatus, JobType } from '../types/api';

export default function History() {
  const [jobs, setJobs] = useState<Job[] | null>(null);
  const [err, setErr] = useState('');
  const [type, setType] = useState<'all' | JobType>('all');
  const [status, setStatus] = useState<'all' | JobStatus>('all');
  const [q, setQ] = useState('');

  const load = useCallback(() => { setErr(''); api.jobs.list().then(setJobs).catch((e) => setErr((e as Error).message)); }, []);
  useEffect(load, [load]);

  const shown = (jobs ?? []).filter((j) => (type === 'all' || j.type === type) && (status === 'all' || j.status === status) && (`#${j.id} ${j.problem_id ?? 'custom'}`).toLowerCase().includes(q.toLowerCase()));

  return (
    <>
      <PageHeader title="History" description="Every analysis, optimization and training run on your account."
        actions={<Button variant="secondary" icon={<RefreshCw className="h-4 w-4" />} onClick={load}>Refresh</Button>} />
      <div className="mb-5 flex flex-wrap items-center gap-3">
        <div className="relative"><Search className="pointer-events-none absolute left-3 top-2.5 h-4 w-4 text-mute" /><input className="field !w-64 !pl-9" placeholder="Search by id or problem" aria-label="Search history" value={q} onChange={(e) => setQ(e.target.value)} /></div>
        <Segmented value={type} onChange={setType} label="Filter by type" options={[{ value: 'all', label: 'All' }, { value: 'analyze', label: 'Analysis' }, { value: 'optimize', label: 'Optimization' }, { value: 'train', label: 'Training' }]} />
        <select className="field !w-40" aria-label="Filter by status" value={status} onChange={(e) => setStatus(e.target.value as 'all' | JobStatus)}>
          {['all', 'queued', 'running', 'done', 'failed', 'cancelled'].map((s) => <option key={s} value={s}>{s === 'all' ? 'Any status' : s}</option>)}
        </select>
      </div>
      {err && <ErrorBox title="Could not load your history" action={<Button size="sm" variant="secondary" onClick={load}>Try again</Button>}>{err}</ErrorBox>}
      {!jobs && !err && <Loading label="Loading history" />}
      {jobs && jobs.length === 0 && <EmptyState title="Nothing here yet" action={<Link to="/analyze"><Button>Analyze your first program</Button></Link>}>Your analyses will appear here as soon as you run one.</EmptyState>}
      {jobs && jobs.length > 0 && shown.length === 0 && <EmptyState title="No jobs match these filters">Clear the search or choose a different type or status.</EmptyState>}
      {shown.length > 0 && (
        <div className="overflow-x-auto rounded-xl border border-line bg-panel">
          <table className="w-full text-left text-sm">
            <thead><tr className="border-b border-line text-mute"><th className="px-5 py-3 font-medium">Job</th><th className="px-5 py-3 font-medium">Type</th><th className="px-5 py-3 font-medium">Problem</th><th className="px-5 py-3 font-medium">Status</th><th className="px-5 py-3 font-medium">Started</th></tr></thead>
            <tbody>
              {shown.map((j) => (
                <tr key={j.id} className="border-b border-line last:border-0 hover:bg-raised/60">
                  <td className="px-5 py-3"><Link to={jobHref(j)} className="font-medium text-accent hover:underline">#{j.id}</Link></td>
                  <td className="px-5 py-3">{typeLabel[j.type]}</td>
                  <td className="px-5 py-3 font-mono text-mute">{j.type === 'train' ? '-' : j.problem_id ?? 'custom'}</td>
                  <td className="px-5 py-3"><Badge tone={statusTone[j.status]}>{j.status}</Badge></td>
                  <td className="px-5 py-3 text-mute">{relTime(j.created_at)}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      )}
    </>
  );
}
