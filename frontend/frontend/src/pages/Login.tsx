import { useState, type FormEvent } from 'react';
import { useAuth } from '../hooks/useAuth';
import { Button, ErrorBox, Segmented } from '../components/common/ui';
import { LogoMark } from '../components/layout/Logo';
import { PIPELINE } from '../lib/pipeline';

export default function Login() {
  const { login, signup } = useAuth();
  const [mode, setMode] = useState<'login' | 'signup'>('login');
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [busy, setBusy] = useState(false);
  const [err, setErr] = useState('');

  const submit = async (e: FormEvent) => {
    e.preventDefault();
    setErr(''); setBusy(true);
    try { await (mode === 'login' ? login : signup)(username.trim(), password); } catch (x) { setErr((x as Error).message); } finally { setBusy(false); }
  };

  return (
    <div className="grid min-h-screen lg:grid-cols-[1.1fr_1fr]">
      <div className="hidden flex-col justify-between border-r border-line bg-panel p-12 lg:flex">
        <div className="flex items-center gap-3"><LogoMark size={36} /><span className="font-display text-2xl font-bold">NeuroCode</span></div>
        <div>
          <h1 className="max-w-lg text-5xl font-bold leading-[1.08]">Know what your code does, and how fast it does it.</h1>
          <p className="mt-5 max-w-md text-lg text-mute">Paste a C++ solution. NeuroCode reads its structure, derives its complexity, tests it against a reference, and proposes a verified faster version.</p>
          <ol className="mt-10 grid max-w-md grid-cols-3 gap-x-6 gap-y-3 text-sm text-mute">
            {PIPELINE.map((s, i) => <li key={s.label} className="flex items-center gap-2"><span className="flex h-5 w-5 items-center justify-center rounded-full border border-line text-xs">{i + 1}</span>{s.label}</li>)}
          </ol>
        </div>
        <p className="text-sm text-mute">Deterministic analysis is the foundation. The model is the advisor.</p>
      </div>
      <div className="flex items-center justify-center p-8">
        <form onSubmit={submit} className="w-full max-w-sm space-y-5">
          <div><h2 className="text-3xl font-bold">{mode === 'login' ? 'Sign in' : 'Create your account'}</h2>
            <p className="mt-1 text-mute">{mode === 'login' ? 'Pick up where you left off.' : 'Your analyses are saved to your account.'}</p></div>
          <Segmented value={mode} onChange={setMode} label="Account mode" options={[{ value: 'login', label: 'Sign in' }, { value: 'signup', label: 'Sign up' }]} />
          {err && <ErrorBox title={mode === 'login' ? 'Could not sign in' : 'Could not create the account'}>{err}</ErrorBox>}
          <div><label htmlFor="u" className="label">Username</label><input id="u" className="field" autoComplete="username" required minLength={3} value={username} onChange={(e) => setUsername(e.target.value)} /></div>
          <div><label htmlFor="p" className="label">Password</label><input id="p" type="password" className="field" autoComplete={mode === 'login' ? 'current-password' : 'new-password'} required minLength={8} value={password} onChange={(e) => setPassword(e.target.value)} />
            {mode === 'signup' && <p className="hint">At least 8 characters.</p>}</div>
          <Button type="submit" size="lg" className="w-full" loading={busy}>{mode === 'login' ? 'Sign in' : 'Create account'}</Button>
        </form>
      </div>
    </div>
  );
}
