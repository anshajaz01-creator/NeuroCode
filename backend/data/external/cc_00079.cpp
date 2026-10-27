#include <bits/stdc++.h>
using namespace std;
template <typename T>
void chkmin(T &x, T y) {
  if (y < x) x = y;
}
int read() {
  int X = 0, w = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') w = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') X = X * 10 + c - '0', c = getchar();
  return X * w;
}
const int N = 200 + 10;
const long long inf = 0x3f3f3f3f3f3f3f3f;
int n, t, s;
long long a[N], b[N], c[N], sa[N], sb[N];
long long f[N][N][2], g[N][N][2];
int main() {
  n = read(), t = read(), s = read();
  for (int i = 1; i <= n; ++i) a[i] = read(), b[i] = read(), c[i] = read();
  ++n, a[n] = b[n] = 2e9, c[n] = inf;
  for (int i = 1; i <= n; ++i)
    sa[i] = sa[i - 1] + a[i], sb[i] = sb[i - 1] + b[i];
  memset(f, 0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g));
  for (int i = 0; i <= t; ++i)
    f[0][i][0] = f[0][i][1] = g[0][i][0] = g[0][i][1] = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= t; ++j)
      for (int k = 0; k <= 1; ++k) {
        if (k * a[i] + j * b[i] <= c[i] && f[i - 1][j][k] != inf) {
          chkmin(f[i][j][k], f[i - 1][j][k]);
          long long cnt = (k * sa[i - 1] + j * sb[i - 1] + s - 1) / s;
          if (cnt * s <= k * sa[i] + j * sb[i]) chkmin(g[i][j][k], cnt);
        }
        for (int p = 0; p < j; ++p) {
          if (g[i][p][k] == inf) continue;
          long long res = k * sa[i] + p * sb[i] - s * g[i][p][k];
          long long need = (max(res + (j - p) * b[i] - c[i], 0ll) + s - 1) / s;
          if (need * s <= res && f[i - 1][j - p][0] != inf) {
            chkmin(f[i][j][k], g[i][p][k] + need + f[i - 1][j - p][0]);
            long long cnt = ((j - p) * sb[i - 1] + s - 1) / s;
            if (cnt * s <= (j - p) * sb[i] + res - need * s)
              chkmin(g[i][j][k], g[i][p][k] + need + cnt);
          }
        }
      }
  printf("%lld\n", f[n][t][1]);
  return 0;
}
