import { Navigate, Route, Routes } from 'react-router-dom';
import AppShell from './components/layout/AppShell';
import { Loading } from './components/common/ui';
import { useAuth } from './hooks/useAuth';
import Analyzer from './pages/Analyzer';
import History from './pages/History';
import Login from './pages/Login';
import Optimization from './pages/Optimization';
import Results from './pages/Results';
import Training from './pages/Training';

export default function App() {
  const { user, loading } = useAuth();
  if (loading) return <Loading label="Restoring your session" />;
  if (!user) return <Routes><Route path="/login" element={<Login />} /><Route path="*" element={<Navigate to="/login" replace />} /></Routes>;
  return (
    <Routes>
      <Route element={<AppShell />}>
        <Route path="/" element={<Navigate to="/analyze" replace />} />
        <Route path="/analyze" element={<Analyzer />} />
        <Route path="/jobs/:id" element={<Results />} />
        <Route path="/optimize/:id" element={<Optimization />} />
        <Route path="/history" element={<History />} />
        <Route path="/training" element={<Training />} />
        <Route path="/login" element={<Navigate to="/analyze" replace />} />
        <Route path="*" element={<Navigate to="/analyze" replace />} />
      </Route>
    </Routes>
  );
}
