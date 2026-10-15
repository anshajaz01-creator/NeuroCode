#include <bits/stdc++.h>
using namespace std;
const int maxn = 52;
const int MOD = 1000000007;
int n, p, c[maxn];
int64_t f[maxn][maxn][maxn][maxn], pw2[maxn];
int64_t Choose(int x, int parity) {
  if (x == 0) return parity == 0;
  return pw2[x - 1];
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> p;
  pw2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    cin >> c[i];
    pw2[i] = pw2[i - 1] * 2 % MOD;
  }
  int64_t ans = 0;
  f[n + 1][0][0][0] = 1;
  for (int i = n; i >= 1; --i) {
    for (int x1 = 0; x1 <= n; ++x1) {
      for (int x2 = 0; x2 <= n; ++x2) {
        for (int x3 = 0; x1 + x2 + x3 <= n - i + 1; ++x3) {
          int x4 = n - i + 1 - x1 - x2 - x3;
          if (i == 3 && x1 + x2 + x3 == 0)
            cerr << "pw2[x2 - 1]"
                 << " = " << pw2[x2 - 1] << '\n';
          ;
          int64_t res = 0;
          if (c[i] != 1) {
            if (x1 > 0)
              res += f[i + 1][x1 - 1][x2][x3] * Choose(x4, 1) % MOD * pw2[x3] %
                     MOD * pw2[x2] % MOD * pw2[x1 - 1] % MOD;
            if (x2 > 0)
              res += f[i + 1][x1][x2 - 1][x3] * Choose(x4, 0) % MOD * pw2[x3] %
                     MOD * pw2[x1] % MOD * pw2[x2 - 1] % MOD;
          }
          if (c[i] != 0) {
            if (x3 > 0)
              res += f[i + 1][x1][x2][x3 - 1] * Choose(x2, 1) % MOD * pw2[x1] %
                     MOD * pw2[x4] % MOD * pw2[x3 - 1] % MOD;
            if (x4 > 0)
              res += f[i + 1][x1][x2][x3] * Choose(x2, 0) % MOD * pw2[x1] %
                     MOD * pw2[x3] % MOD * pw2[x4 - 1] % MOD;
          }
          f[i][x1][x2][x3] = res % MOD;
          if (i == 1 && (x2 + x4) % 2 == p) ans = (ans + res) % MOD;
        }
      }
    }
  }
  cout << ans;
}
