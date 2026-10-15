#include <bits/stdc++.h>
inline void chkmin(long long& a, long long b) {
  if (a > b) a = b;
}
const int N = 205;
const long long INF = 0x3f3f3f3f3f3f3f3fll;
int n, t, K, a[N], b[N];
long long sa[N], sb[N], c[N], f[N][N][2], g[N][N][2];
int main() {
  scanf("%d%d%d", &n, &t, &K);
  long long times, rem, need, times2;
  for (int i = 1; i <= n; ++i) scanf("%d%d%lld", &a[i], &b[i], &c[i]);
  ++n;
  a[n] = b[n] = INT_MAX;
  c[n] = INF;
  for (int i = 1; i <= n; ++i)
    sa[i] = sa[i - 1] + a[i], sb[i] = sb[i - 1] + b[i];
  memset(f, 0x3f, sizeof(f));
  memset(f[0], 0, sizeof(f[0]));
  memset(g, 0x3f, sizeof(f));
  memset(g[0], 0, sizeof(g[0]));
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= t; ++j)
      for (int k = 0; k < 2; ++k) {
        if ((long long)k * a[i] + (long long)j * b[i] <= c[i] &&
            f[i - 1][j][k] < INF) {
          chkmin(f[i][j][k], f[i - 1][j][k]);
          times = (k * sa[i - 1] + j * sb[i - 1] + K - 1) / K;
          if (times * K <= k * sa[i] + j * sb[i]) chkmin(g[i][j][k], times);
        }
        for (int r = 0; r < j; ++r)
          if ((times = g[i][r][k]) < INF) {
            rem = k * sa[i] + r * sb[i] - times * K;
            need = (std::max(0ll, rem + (long long)(j - r) * b[i] - c[i]) + K -
                    1) /
                   K;
            if (need * K <= rem && f[i - 1][j - r][0] < INF) {
              chkmin(f[i][j][k], times + need + f[i - 1][j - r][0]);
              times2 = ((j - r) * sb[i - 1] + K - 1) / K;
              if (times2 * K <= (j - r) * sb[i] + (rem - need * K)) {
                chkmin(g[i][j][k], times + need + times2);
              }
            }
          }
      }
  return printf("%lld\n", f[n][t][1]), 0;
}
