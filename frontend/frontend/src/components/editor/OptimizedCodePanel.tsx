import { Check, Copy, Download, PencilLine } from 'lucide-react';
import { useState } from 'react';
import { Button } from '../common/ui';
import CodeEditor from './CodeEditor';

export default function OptimizedCodePanel({ code, onUse }: { code: string; onUse: () => void }) {
  const [copied, setCopied] = useState(false);
  const copy = async () => { await navigator.clipboard.writeText(code); setCopied(true); setTimeout(() => setCopied(false), 1500); };
  const download = () => {
    const a = document.createElement('a');
    a.href = URL.createObjectURL(new Blob([code], { type: 'text/plain' }));
    a.download = 'optimized.cpp';
    a.click();
    URL.revokeObjectURL(a.href);
  };
  return (
    <div>
      <div className="mb-3 flex flex-wrap gap-2">
        <Button size="sm" variant="secondary" onClick={() => void copy()} icon={copied ? <Check className="h-4 w-4" /> : <Copy className="h-4 w-4" />}>{copied ? 'Copied' : 'Copy code'}</Button>
        <Button size="sm" variant="secondary" onClick={download} icon={<Download className="h-4 w-4" />}>Download .cpp</Button>
        <Button size="sm" variant="secondary" onClick={onUse} icon={<PencilLine className="h-4 w-4" />}>Open in editor</Button>
      </div>
      <CodeEditor value={code} readOnly height="420px" />
    </div>
  );
}
