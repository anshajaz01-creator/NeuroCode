import { createContext, useContext, useEffect, useState, type ReactNode } from 'react';

export interface Settings { theme: 'dark' | 'light'; fontSize: number; minimap: boolean; wordWrap: boolean }
const DEFAULTS: Settings = { theme: 'dark', fontSize: 14, minimap: false, wordWrap: false };
const Ctx = createContext<{ settings: Settings; update: (p: Partial<Settings>) => void } | null>(null);

export function SettingsProvider({ children }: { children: ReactNode }) {
  const [settings, set] = useState<Settings>(() => {
    try { return { ...DEFAULTS, ...JSON.parse(localStorage.getItem('nc.settings') || '{}') }; } catch { return DEFAULTS; }
  });
  useEffect(() => {
    document.documentElement.classList.toggle('dark', settings.theme === 'dark');
    localStorage.setItem('nc.settings', JSON.stringify(settings));
  }, [settings]);
  return <Ctx.Provider value={{ settings, update: (p) => set((s) => ({ ...s, ...p })) }}>{children}</Ctx.Provider>;
}

export function useSettings() {
  const c = useContext(Ctx);
  if (!c) throw new Error('useSettings outside SettingsProvider');
  return c;
}
