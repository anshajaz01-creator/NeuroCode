const V1 = '/api/v1';
export const E = {
  login: `${V1}/auth/login`,
  signup: `${V1}/auth/signup`,
  logout: `${V1}/auth/logout`,
  me: `${V1}/auth/me`,
  jobs: `${V1}/jobs`,
  job: (id: number) => `${V1}/jobs/${id}`,
  cancel: (id: number) => `${V1}/jobs/${id}/cancel`,
  problems: `${V1}/problems`,
  execute: `${V1}/execute`,
  models: `${V1}/models`,
  train: `${V1}/models/train`,
  activate: (id: number) => `${V1}/models/${id}/activate`,
  health: `${V1}/health`,
  ws: (id: number) => `/ws/jobs/${id}`,
};
