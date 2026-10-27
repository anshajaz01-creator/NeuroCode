import { DiffEditor } from '@monaco-editor/react';
import { useState } from 'react';
import { useSettings } from '../../hooks/useSettings';
import { Loading, Segmented } from '../common/ui';

export default function DiffViewer({ original, modified }: { original: string; modified: string }) {
  const { settings } = useSettings();
  const [mode, setMode] = useState<'split' | 'inline'>('split');
  return (
    <div>
      <div className="mb-3 flex items-center justify-between">
        <div className="flex gap-6 text-sm text-mute"><span>Original</span><span>Optimized</span></div>
        <Segmented value={mode} onChange={setMode} label="Diff layout" options={[{ value: 'split', label: 'Side by side' }, { value: 'inline', label: 'Inline' }]} />
      </div>
      <div className="overflow-hidden rounded-lg border border-line" style={{ height: 460 }}>
        <DiffEditor original={original} modified={modified} language="cpp" theme={settings.theme === 'dark' ? 'vs-dark' : 'light'} loading={<Loading label="Loading diff" />}
          options={{ readOnly: true, renderSideBySide: mode === 'split', fontSize: settings.fontSize, fontFamily: 'JetBrains Mono, monospace', minimap: { enabled: false }, scrollBeyondLastLine: false, automaticLayout: true }} />
      </div>
    </div>
  );
}
