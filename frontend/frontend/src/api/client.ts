import type {
  AuthResponse, CreateJobRequest, ExecuteRequest, ExecuteResponse, Job, ModelInfo, Problem, TrainRequest, User,
} from '../types/api';
import { E } from './endpoints';
import { mockHandle } from './mock';

export const USE_MOCK = import.meta.env.VITE_USE_MOCK === 'true';
const BASE = import.meta.env.VITE_API_BASE ?? '';
const TOKEN_KEY = 'nc.token';

export const getToken = () => localStorage.getItem(TOKEN_KEY);
export const setToken = (t: string | null) => (t ? localStorage.setItem(TOKEN_KEY, t) : localStorage.removeItem(TOKEN_KEY));

export class ApiError extends Error {
  constructor(public status: number, message: string) { super(message); }
}

async function request<T>(method: string, path: string, body?: unknown): Promise<T> {
  if (USE_MOCK) return (await mockHandle(method, path, body)) as T;
  const token = getToken();
  const res = await fetch(BASE + path, {
    method,
    headers: {
      ...(body !== undefined ? { 'Content-Type': 'application/json' } : {}),
      ...(token ? { Authorization: `Bearer ${token}` } : {}),
    },
    body: body !== undefined ? JSON.stringify(body) : undefined,
  });
  if (res.status === 401 && path !== E.login) window.dispatchEvent(new Event('nc:unauthorized'));
  if (!res.ok) {
    let msg = res.statusText;
    try { const j = await res.json(); msg = j.error ?? j.message ?? msg; } catch { /* non-JSON error body */ }
    throw new ApiError(res.status, msg || `Request failed (${res.status})`);
  }
  const text = await res.text();
  return (text ? JSON.parse(text) : undefined) as T;
}

export const api = {
  auth: {
    login: (username: string, password: string) => request<AuthResponse>('POST', E.login, { username, password }),
    signup: (username: string, password: string) => request<AuthResponse>('POST', E.signup, { username, password }),
    logout: () => request<void>('POST', E.logout),
    me: () => request<User>('GET', E.me),
  },
  jobs: {
    create: (b: CreateJobRequest) => request<{ job_id: number }>('POST', E.jobs, b),
    get: (id: number) => request<Job>('GET', E.job(id)),
    list: () => request<Job[]>('GET', E.jobs),
    cancel: (id: number) => request<void>('POST', E.cancel(id)),
  },
  problems: { list: () => request<Problem[]>('GET', E.problems) },
  execute: (b: ExecuteRequest) => request<ExecuteResponse>('POST', E.execute, b),
  models: {
    list: () => request<ModelInfo[]>('GET', E.models),
    train: (b: TrainRequest) => request<{ job_id: number }>('POST', E.train, b),
    activate: (id: number) => request<void>('POST', E.activate(id)),
  },
};
