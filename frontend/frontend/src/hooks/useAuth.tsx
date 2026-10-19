import { createContext, useCallback, useContext, useEffect, useState, type ReactNode } from 'react';
import { api, getToken, setToken } from '../api/client';
import type { User } from '../types/api';

interface AuthCtx {
  user: User | null; loading: boolean;
  login: (u: string, p: string) => Promise<void>;
  signup: (u: string, p: string) => Promise<void>;
  logout: () => Promise<void>;
}
const Ctx = createContext<AuthCtx | null>(null);

export function AuthProvider({ children }: { children: ReactNode }) {
  const [user, setUser] = useState<User | null>(null);
  const [loading, setLoading] = useState(!!getToken());

  useEffect(() => {
    if (!getToken()) return;
    api.auth.me().then(setUser).catch(() => setToken(null)).finally(() => setLoading(false));
  }, []);
  useEffect(() => {
    const h = () => { setToken(null); setUser(null); };
    window.addEventListener('nc:unauthorized', h);
    return () => window.removeEventListener('nc:unauthorized', h);
  }, []);

  const finish = (r: { token: string; user: User }) => { setToken(r.token); setUser(r.user); };
  const login = useCallback(async (u: string, p: string) => finish(await api.auth.login(u, p)), []);
  const signup = useCallback(async (u: string, p: string) => finish(await api.auth.signup(u, p)), []);
  const logout = useCallback(async () => { try { await api.auth.logout(); } catch { /* token may already be gone */ } setToken(null); setUser(null); }, []);

  return <Ctx.Provider value={{ user, loading, login, signup, logout }}>{children}</Ctx.Provider>;
}

export function useAuth() {
  const c = useContext(Ctx);
  if (!c) throw new Error('useAuth outside AuthProvider');
  return c;
}
