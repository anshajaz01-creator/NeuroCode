const c = (v) => `rgb(var(--${v}) / <alpha-value>)`;
/** @type {import('tailwindcss').Config} */
export default {
  darkMode: 'class',
  content: ['./index.html', './src/**/*.{ts,tsx}'],
  theme: {
    extend: {
      colors: { bg: c('bg'), panel: c('panel'), raised: c('raised'), line: c('line'), ink: c('ink'), mute: c('mute'), accent: c('accent'), ok: c('ok'), warn: c('warn'), bad: c('bad') },
      fontFamily: {
        display: ['"Bricolage Grotesque"', 'ui-sans-serif', 'system-ui', 'sans-serif'],
        sans: ['"Instrument Sans"', 'ui-sans-serif', 'system-ui', 'sans-serif'],
        mono: ['"JetBrains Mono"', 'ui-monospace', 'SFMono-Regular', 'Menlo', 'monospace'],
      },
      keyframes: {
        ring: { '0%': { boxShadow: '0 0 0 0 rgb(var(--accent) / .55)' }, '100%': { boxShadow: '0 0 0 10px rgb(var(--accent) / 0)' } },
        rise: { from: { opacity: 0, transform: 'translateY(6px)' }, to: { opacity: 1, transform: 'none' } },
      },
      animation: { ring: 'ring 1.4s ease-out infinite', rise: 'rise .25s ease-out both' },
    },
  },
  plugins: [],
};
