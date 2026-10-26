import { BookOpen, Eraser, Play, Settings2, Terminal } from 'lucide-react';
import { useState } from 'react';
import { useSettings } from '../../hooks/useSettings';
import { SAMPLES, type Sample } from '../../lib/samples';
import { Button, Toggle } from '../common/ui';

export default function EditorToolbar({ onPick, onClear, onRun, running, consoleOpen, onToggleConsole }:
  { onPick: (s: Sample) => void; onClear: () => void; onRun: () => void; running: boolean; consoleOpen: boolean; onToggleConsole: () => void }) {
  const { settings, update } = useSettings();
  const [menu, setMenu] = useState<'samples' | 'settings' | null>(null);
  const toggle = (m: 'samples' | 'settings') => setMenu((c) => (c === m ? null : m));
  return (
    <div className="relative mb-3 flex flex-wrap items-center gap-2">
      <span className="mr-auto font-mono text-sm text-mute">main.cpp</span>
      <Button size="sm" variant="secondary" icon={<BookOpen className="h-4 w-4" />} onClick={() => toggle('samples')} aria-expanded={menu === 'samples'}>Examples</Button>
      <Button size="sm" variant="secondary" icon={<Settings2 className="h-4 w-4" />} onClick={() => toggle('settings')} aria-expanded={menu === 'settings'}>Editor</Button>
      <Button size="sm" variant="ghost" icon={<Eraser className="h-4 w-4" />} onClick={onClear}>Clear</Button>
      <Button size="sm" variant="secondary" icon={<Terminal className="h-4 w-4" />} onClick={onToggleConsole}>{consoleOpen ? 'Hide console' : 'Console'}</Button>
      <Button size="sm" variant="secondary" icon={<Play className="h-4 w-4" />} loading={running} onClick={onRun}>Run</Button>
      {menu === 'samples' && (
        <div className="absolute right-0 top-10 z-20 w-72 rounded-xl border border-line bg-panel p-2 shadow-xl">
          {SAMPLES.map((s) => (
            <button key={s.id} onClick={() => { onPick(s); setMenu(null); }} className="block w-full rounded-lg px-3 py-2 text-left text-sm hover:bg-raised">{s.title}</button>
          ))}
        </div>
      )}
      {menu === 'settings' && (
        <div className="absolute right-0 top-10 z-20 w-72 space-y-3 rounded-xl border border-line bg-panel p-4 shadow-xl">
          <label className="flex items-center justify-between gap-4 text-sm">Font size
            <select className="field !w-24" value={settings.fontSize} onChange={(e) => update({ fontSize: Number(e.target.value) })}>
              {[12, 13, 14, 16, 18, 20].map((n) => <option key={n} value={n}>{n}px</option>)}
            </select>
          </label>
          <Toggle label="Minimap" checked={settings.minimap} onChange={(v) => update({ minimap: v })} />
          <Toggle label="Wrap long lines" checked={settings.wordWrap} onChange={(v) => update({ wordWrap: v })} />
        </div>
      )}
    </div>
  );
}
