export function LogoMark({ size = 28 }: { size?: number }) {
  return (
    <svg width={size} height={size} viewBox="0 0 32 32" fill="none" aria-hidden>
      <rect width="32" height="32" rx="8" fill="rgb(var(--accent))" />
      <path d="M9 22V10l14 12V10" stroke="rgb(var(--bg))" strokeWidth="2.6" strokeLinecap="round" strokeLinejoin="round" />
      <circle cx="9" cy="10" r="2" fill="rgb(var(--bg))" /><circle cx="23" cy="22" r="2" fill="rgb(var(--bg))" />
    </svg>
  );
}
