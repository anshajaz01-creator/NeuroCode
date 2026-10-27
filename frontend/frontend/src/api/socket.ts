import type { WsEvent } from '../types/api';
import { E } from './endpoints';
import { USE_MOCK, getToken } from './client';
import { mockSubscribe } from './mock';

/** Subscribe to live job events. Returns an unsubscribe function. Reconnects with backoff. */
export function subscribeJob(jobId: number, onEvent: (e: WsEvent) => void, onState: (connected: boolean) => void): () => void {
  if (USE_MOCK) return mockSubscribe(jobId, onEvent, onState);

  let ws: WebSocket | null = null;
  let closed = false;
  let retry = 0;
  let timer: number | undefined;

  const open = () => {
    const proto = location.protocol === 'https:' ? 'wss' : 'ws';
    const host = import.meta.env.VITE_WS_BASE || `${proto}://${location.host}`;
    // Browsers cannot set headers on a WebSocket, so the token travels as a query parameter.
    ws = new WebSocket(`${host}${E.ws(jobId)}?token=${encodeURIComponent(getToken() ?? '')}`);
    ws.onopen = () => { retry = 0; onState(true); };
    ws.onmessage = (m) => {
      try { onEvent(JSON.parse(m.data) as WsEvent); } catch { /* ignore malformed frame */ }
    };
    ws.onclose = () => {
      onState(false);
      if (closed) return;
      timer = window.setTimeout(open, Math.min(8000, 500 * 2 ** retry++));
    };
    ws.onerror = () => ws?.close();
  };
  open();

  return () => { closed = true; window.clearTimeout(timer); ws?.close(); };
}
