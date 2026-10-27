import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

// Drogon runs on :8080 (backend/config.json). Proxying keeps the browser same-origin,
// so there is no CORS setup to fight with in development.
export default defineConfig({
  plugins: [react()],
  server: {
    port: 5173,
    proxy: {
      '/api': { target: 'http://localhost:8080', changeOrigin: true },
      '/ws': { target: 'ws://localhost:8080', ws: true },
    },
  },
});
