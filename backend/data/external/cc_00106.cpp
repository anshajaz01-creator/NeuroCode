#include <bits/stdc++.h>
using namespace std;
const int N = 3005, P = 998244353;
using ll = long long;
int n, c, a[N], ans[N], b[N];
int f[N][1 << 11], g[N][305];
ll pw[N], inv[N];
ll qpow(ll a, ll b) {
  ll ret = 1;
  while (b) {
    if (b & 1) ret = ret * a % P;
    a = a * a % P;
    b >>= 1;
  }
  return ret;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> c;
  for (int i = 1; i <= n; i++) cin >> a[i];
  if (c <= 11) {
    auto add = [](int &a, ll b) { a = (a * 2 + b) % P; };
    int mx = 0, all = (1 << c) - 1;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
      int aa = a[i] - 1;
      for (int j = 0; j <= mx; j++)
        for (int k = 0; k < (1 << (c - aa - 1)); k++)
          for (int l = 0; l < (1 << aa); l++)
            add(f[j][(k << (aa + 1)) + (1 << aa) + l],
                f[j][(k << (aa + 1)) + l]);
      for (int j = 0; j <= mx; j++)
        if (f[j][all]) {
          f[j + 1][0] = (f[j + 1][0] + f[j][all]) % P;
          f[j][all] = 0;
          if (mx == j) ++mx;
        }
    }
    for (int i = 0; i <= n / c; i++) {
      ll tt = 0;
      for (int j = 0; j <= all; j++) tt += f[i][j];
      ans[i] = tt % P;
    }
  } else {
    pw[0] = 1;
    for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * 2 % P;
    for (int i = 0; i <= n; i++) inv[i] = qpow(pw[i] - 1, P - 2);
    inv[0] = 1;
    g[0][0] = 1;
    for (int i = 0; i <= n; i++) {
      int mx = i / c, all = 0;
      ll sum = pw[n - i], t1, t2 = 1;
      for (int j = 1; j <= c; j++) b[j] = 0;
      for (int j = i + 1; j <= n; j++) {
        if (!b[a[j]]++) ++all;
        t1 = t2 * inv[b[a[j]] - 1] % P;
        t2 = t1 * (pw[b[a[j]]] - 1) % P;
        if (all == c) {
          sum = (sum - t1 * pw[n - j] % P + P) % P;
          for (int k = 0; k <= mx; k++)
            g[j][k + 1] = (g[i][k] * 1ll * t1 + g[j][k + 1]) % P;
        }
      }
      for (int j = 0; j <= mx; j++) ans[j] = (g[i][j] * sum + ans[j]) % P;
    }
  }
  ans[0] = (ans[0] + P - 1) % P;
  for (int i = 0; i <= n; i++) cout << ans[i] << ' ';
  return 0;
}
