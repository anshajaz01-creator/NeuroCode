#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int N = 210;
const int mod = 0;
int gi() {
  int x = 0, o = 1;
  char ch = getchar();
  while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
  if (ch == '-') o = -1, ch = getchar();
  while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
  return x * o;
}
template <typename T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, 1 : 0;
};
template <typename T>
bool chkmin(T &a, T b) {
  return a > b ? a = b, 1 : 0;
};
int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
void inc(int &a, int b) { a = (a + b >= mod ? a + b - mod : a + b); }
void dec(int &a, int b) { a = (a - b < 0 ? a - b + mod : a - b); }
int n, t;
long long k, a[N], b[N], c[N], sa[N], sb[N], d[N][N][2], g[N][N][2];
int main() {
  n = gi(), t = gi(), k = gi();
  for (int i = 1; i <= n; i++) a[i] = gi(), b[i] = gi(), c[i] = gi();
  ++n, a[n] = c[n] = inf;
  for (int i = 1; i <= n; i++)
    sa[i] = sa[i - 1] + a[i], sb[i] = sb[i - 1] + b[i];
  for (int p = 1; p <= n; p++)
    for (int s = 0; s <= t; s++)
      for (int z = 0; z < 2; z++) {
        d[p][s][z] = g[p][s][z] = inf;
        if (z * a[p] + s * b[p] <= c[p] && d[p - 1][s][z] < inf) {
          d[p][s][z] = d[p - 1][s][z];
          long long val = (z * sa[p - 1] + s * sb[p - 1] + k - 1) / k;
          if (val * k <= z * sa[p] + s * sb[p]) g[p][s][z] = val;
        }
        for (int r = 0; r < s; r++)
          if (g[p][r][z] < inf) {
            long long m = z * sa[p] + r * sb[p] - k * g[p][r][z];
            long long x = (max(m + (s - r) * b[p] - c[p], 0ll) + k - 1) / k;
            if (x * k <= m && d[p - 1][s - r][0] < inf) {
              chkmin(d[p][s][z], g[p][r][z] + x + d[p - 1][s - r][0]);
              long long val = (sb[p - 1] * (s - r) + k - 1) / k;
              if (val * k <= sb[p] * (s - r) + m - x * k)
                chkmin(g[p][s][z], g[p][r][z] + x + val);
            }
          }
      }
  cout << d[n][t][1];
  return 0;
}
