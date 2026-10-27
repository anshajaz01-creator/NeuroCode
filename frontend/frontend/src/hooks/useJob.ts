import { useCallback, useEffect, useState } from 'react';
import { api } from '../api/client';
import { isTerminal } from '../lib/format';
import type { Job } from '../types/api';
import { useProgressSocket } from './useProgressSocket';

/** Loads a job, shows live progress over the socket, and polls as a fallback until it finishes. */
export function useJob(id?: number) {
  const [job, setJob] = useState<Job | null>(null);
  const [error, setError] = useState<string | null>(null);
  const active = job && !isTerminal(job.status) ? job.id : undefined;
  const live = useProgressSocket(active);

  const refresh = useCallback(async () => {
    if (id === undefined || Number.isNaN(id)) return;
    try { setJob(await api.jobs.get(id)); setError(null); } catch (e) { setError((e as Error).message); }
  }, [id]);

  useEffect(() => { setJob(null); setError(null); void refresh(); }, [refresh]);
  useEffect(() => {
    if (!job || isTerminal(job.status)) return;
    const t = window.setInterval(refresh, 1500);
    return () => window.clearInterval(t);
  }, [job, refresh]);
  useEffect(() => { if (live.done) void refresh(); }, [live.done, refresh]);

  return { job, error, live, refresh };
}
