import { useEffect, useState } from 'react';
import { subscribeJob } from '../api/socket';
import type { EpochMetrics } from '../types/api';

export interface LiveState { percent: number; stage: string; connected: boolean; epochs: EpochMetrics[]; done: boolean; error: string | null }
const EMPTY: LiveState = { percent: 0, stage: '', connected: false, epochs: [], done: false, error: null };

export function useProgressSocket(jobId?: number): LiveState {
  const [s, setS] = useState<LiveState>(EMPTY);
  useEffect(() => {
    setS(EMPTY);
    if (jobId === undefined) return;
    return subscribeJob(
      jobId,
      (e) => setS((p) => {
        if (e.type === 'progress') return { ...p, percent: e.percent, stage: e.stage };
        if (e.type === 'epoch') return { ...p, epochs: [...p.epochs, { epoch: e.epoch, train_loss: e.train_loss, val_loss: e.val_loss, val_accuracy: e.val_accuracy }] };
        if (e.type === 'done') return { ...p, done: true };
        return { ...p, error: e.message };
      }),
      (connected) => setS((p) => ({ ...p, connected })),
    );
  }, [jobId]);
  return s;
}
