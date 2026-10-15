#include <bits/stdc++.h>
using namespace std;
long long read() {
  long long x = 0, f = 0;
  char ch = getchar();
  while (!isdigit(ch)) f = ch == '-', ch = getchar();
  while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return f ? -x : x;
}
const int N = 205;
const long long INF = 1e15;
int n, t;
long long k;
long long a[N], b[N], c[N];
long long sa[N], sb[N], sc[N];
long long f[N][N][2], g[N][N][2];
void ckmin(long long &a, long long b) {
  if (a > b) a = b;
}
int main() {
  n = read(), t = read(), k = read();
  for (int i = (1); i <= (n); i++) a[i] = read(), b[i] = read(), c[i] = read();
  ++n, a[n] = INF, b[n] = 0, c[n] = INF;
  for (int i = (1); i <= (n); i++)
    sa[i] = sa[i - 1] + a[i], sb[i] = sb[i - 1] + b[i],
    sc[i] = sc[i - 1] + c[i];
  for (int i = (0); i <= (N - 1); i++)
    for (int j = (0); j <= (N - 1); j++)
      for (int k = (0); k <= (1); k++) f[i][j][k] = g[i][j][k] = INF;
  memset(f[0], 0, sizeof(f[0])), memset(g[0], 0, sizeof(g[0]));
  for (int i = (1); i <= (n); i++)
    for (int j = (0); j <= (t); j++)
      for (int z = (0); z <= (1); z++) {
        if (f[i - 1][j][z] < INF && a[i] * z + b[i] * j <= c[i]) {
          ckmin(f[i][j][z], f[i - 1][j][z]);
          long long val = (sa[i - 1] * z + sb[i] * j + k - 1) / k;
          if (val * k <= sa[i] * z + sb[i] * j) ckmin(g[i][j][z], val);
        }
        for (int r = (0); r <= (j - 1); r++) {
          if (g[i][r][z] >= INF) continue;
          long long rem = sa[i] * z + sb[i] * r - g[i][r][z] * k;
          long long x = (max(rem + (j - r) * b[i] - c[i], 0LL) + k - 1) / k;
          if (x * k > rem || f[i - 1][j - r][0] >= INF) continue;
          ckmin(f[i][j][z], g[i][r][z] + x + f[i - 1][j - r][0]);
          long long val = (sb[i - 1] * (j - r) + k - 1) / k;
          if (val * k <= sb[i] * (j - r) + rem - x * k)
            ckmin(g[i][j][z], g[i][r][z] + x + val);
        }
      }
  cout << f[n][t][1] << endl;
  return 0;
}
