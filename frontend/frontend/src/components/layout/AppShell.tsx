import clsx from 'clsx';
import { FlaskConical, History, LogOut, Moon, ScanSearch, Sun } from 'lucide-react';
import { NavLink, Outlet } from 'react-router-dom';
import { USE_MOCK } from '../../api/client';
import { useAuth } from '../../hooks/useAuth';
import { useSettings } from '../../hooks/useSettings';
import { Badge } from '../common/ui';
import { LogoMark } from './Logo';

const NAV = [
  { to: '/analyze', label: 'Analyze', icon: ScanSearch },
  { to: '/history', label: 'History', icon: History },
  { to: '/training', label: 'Model training', icon: FlaskConical },
];

export default function AppShell() {
  const { user, logout } = useAuth();
  const { settings, update } = useSettings();
  return (
    <div className="flex min-h-screen">
      <aside className="sticky top-0 flex h-screen w-16 shrink-0 flex-col border-r border-line bg-panel lg:w-60">
        <div className="flex h-16 items-center gap-3 px-4"><LogoMark /><span className="hidden font-display text-xl font-bold lg:inline">NeuroCode</span></div>
        <nav className="flex-1 space-y-1 px-2 py-3" aria-label="Main">
          {NAV.map(({ to, label, icon: Icon }) => (
            <NavLink key={to} to={to} title={label}
              className={({ isActive }) => clsx('flex items-center gap-3 rounded-lg px-3 py-2.5 text-sm font-medium transition-colors', isActive ? 'bg-accent/15 text-accent' : 'text-mute hover:bg-raised hover:text-ink')}>
              <Icon className="h-5 w-5 shrink-0" /><span className="hidden lg:inline">{label}</span>
            </NavLink>
          ))}
        </nav>
        <div className="space-y-2 border-t border-line p-3">
          {USE_MOCK && <Badge tone="warn" className="hidden lg:inline-flex">Mock engine</Badge>}
          <div className="hidden truncate px-1 text-sm text-mute lg:block">{user?.username}</div>
          <div className="flex items-center gap-1">
            <button onClick={() => update({ theme: settings.theme === 'dark' ? 'light' : 'dark' })} aria-label="Toggle theme" title="Toggle theme"
              className="rounded-lg p-2 text-mute hover:bg-raised hover:text-ink">{settings.theme === 'dark' ? <Sun className="h-5 w-5" /> : <Moon className="h-5 w-5" />}</button>
            <button onClick={() => void logout()} aria-label="Sign out" title="Sign out" className="rounded-lg p-2 text-mute hover:bg-raised hover:text-ink"><LogOut className="h-5 w-5" /></button>
          </div>
        </div>
      </aside>
      <main className="min-w-0 flex-1 px-5 py-8 lg:px-10"><div className="mx-auto max-w-[1400px]"><Outlet /></div></main>
    </div>
  );
}
