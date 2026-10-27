import { ShieldAlert, ShieldCheck } from 'lucide-react';
import { Badge } from '../common/ui';

export default function VerificationBadge({ verified }: { verified: boolean }) {
  return verified
    ? <Badge tone="ok" className="!px-2.5 !py-1 !text-sm"><ShieldCheck className="h-4 w-4" />Verified against reference</Badge>
    : <Badge tone="warn" className="!px-2.5 !py-1 !text-sm"><ShieldAlert className="h-4 w-4" />Not verified</Badge>;
}
