#include <bits/stdc++.h>
using namespace std;
const int mxn = 225;
const long long INF = 1e17;
long long n, m, i, j, t, k, s, K, f[mxn][mxn][2], g[mxn][mxn][2], a[mxn],
    b[mxn], c[mxn], qza[mxn], qzb[mxn];
int main() {
  scanf("%lld%lld%lld", &n, &m, &K);
  memset(f, 0x3f3f3f3f, sizeof(f));
  memset(g, 0x3f3f3f3f, sizeof(g));
  memset(f, 0, sizeof(f[0]));
  memset(g, 0, sizeof(g[0]));
  for (i = 1; i <= n; ++i)
    scanf("%lld%lld%lld", &a[i], &b[i], &c[i]), qza[i] = qza[i - 1] + a[i],
                                                qzb[i] = qzb[i - 1] + b[i];
  ++n;
  a[n] = 1e12;
  b[n] = 1e12;
  c[n] = 2e18;
  qza[n] = qza[n - 1] + a[n];
  qzb[n] = qzb[n - 1] + b[n];
  for (i = 1; i <= n; ++i)
    for (j = 0; j <= m; ++j) {
      long long tmp;
      if (b[i] * 1ll * j <= c[i] && f[i - 1][j][0] < INF) {
        f[i][j][0] = min(f[i][j][0], f[i - 1][j][0]);
        tmp = (qzb[i - 1] * j + K - 1) / K;
        if (tmp * K <= qzb[i] * j) g[i][j][0] = min(g[i][j][0], tmp);
      }
      if (b[i] * 1ll * j + a[i] <= c[i] && f[i - 1][j][1] < INF) {
        f[i][j][1] = min(f[i][j][1], f[i - 1][j][1]);
        tmp = (qzb[i - 1] * j + qza[i - 1] + K - 1) / K;
        if (tmp * K <= qzb[i] * j + qza[i]) g[i][j][1] = min(g[i][j][1], tmp);
      }
      for (k = j - 1; k >= 0; --k) {
        if (g[i][k][0] < INF) {
          long long rem = qzb[i] * k - K * g[i][k][0],
                    need = (max(0ll, rem + b[i] * (j - k) - c[i]) + K - 1) / K;
          if (need * K <= rem && f[i - 1][j - k][0] < INF) {
            f[i][j][0] =
                min(f[i][j][0], g[i][k][0] + f[i - 1][j - k][0] + need);
            tmp = (qzb[i - 1] * (j - k) + K - 1) / K;
            if (tmp * K <= rem - need * K + qzb[i] * (j - k))
              g[i][j][0] = min(g[i][j][0], g[i][k][0] + need + tmp);
          }
        }
        if (g[i][k][1] < INF) {
          long long rem = qzb[i] * k + qza[i] - K * g[i][k][1],
                    need = (max(0ll, rem + b[i] * (j - k) - c[i]) + K - 1) / K;
          if (need * K <= rem && f[i - 1][j - k][0] < INF) {
            f[i][j][1] =
                min(f[i][j][1], g[i][k][1] + f[i - 1][j - k][0] + need);
            tmp = (qzb[i - 1] * (j - k) + K - 1) / K;
            if (tmp * K <= rem - need * K + qzb[i] * (j - k))
              g[i][j][1] = min(g[i][j][1], g[i][k][1] + need + tmp);
          }
        }
      }
    }
  printf("%lld\n", f[n][m][1]);
  return 0;
}
