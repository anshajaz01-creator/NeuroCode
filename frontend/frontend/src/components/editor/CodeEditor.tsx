import Editor, { type Monaco, type OnMount } from '@monaco-editor/react';
import { useEffect, useRef } from 'react';
import { useSettings } from '../../hooks/useSettings';
import type { Severity } from '../../types/api';
import { Loading } from '../common/ui';

export interface EditorMarker { line: number; message: string; severity: Severity }
type EditorInstance = Parameters<OnMount>[0];

export default function CodeEditor({ value, onChange, readOnly, height = '520px', markers = [] }:
  { value: string; onChange?: (v: string) => void; readOnly?: boolean; height?: string; markers?: EditorMarker[] }) {
  const { settings } = useSettings();
  const ed = useRef<EditorInstance | null>(null);
  const mo = useRef<Monaco | null>(null);

  const applyMarkers = () => {
    const model = ed.current?.getModel();
    if (!model || !mo.current) return;
    const sev = { high: mo.current.MarkerSeverity.Error, medium: mo.current.MarkerSeverity.Warning, low: mo.current.MarkerSeverity.Info };
    mo.current.editor.setModelMarkers(model, 'neurocode', markers.filter((m) => m.line >= 1 && m.line <= model.getLineCount()).map((m) => ({
      startLineNumber: m.line, endLineNumber: m.line, startColumn: 1, endColumn: model.getLineMaxColumn(m.line), message: m.message, severity: sev[m.severity],
    })));
  };
  useEffect(applyMarkers, [markers, value]);

  return (
    <div className="overflow-hidden rounded-lg border border-line" style={{ height }}>
      <Editor language="cpp" value={value} theme={settings.theme === 'dark' ? 'vs-dark' : 'light'} loading={<Loading label="Loading editor" />}
        onChange={(v) => onChange?.(v ?? '')}
        onMount={(e, m) => { ed.current = e; mo.current = m; applyMarkers(); }}
        options={{ readOnly, fontSize: settings.fontSize, fontFamily: 'JetBrains Mono, monospace', minimap: { enabled: settings.minimap }, wordWrap: settings.wordWrap ? 'on' : 'off', scrollBeyondLastLine: false, automaticLayout: true, padding: { top: 12 }, tabSize: 4 }} />
    </div>
  );
}
