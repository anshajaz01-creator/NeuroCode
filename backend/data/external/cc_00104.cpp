#include <bits/stdc++.h>
using namespace std;
const int MOD = (int)998244353;
const int MAXN = (int)3003;
const int LOG = (int)13;
const int infint = (int)1e9 + 3;
const long long inf = (long long)1e12;
int n, c, dp[2][MAXN][1 << LOG], dp2[2][MAXN], f[MAXN][MAXN], Pwr[MAXN],
    Inv[MAXN], a[MAXN], ted[MAXN], ans[MAXN];
inline int add(int a, int b) {
  int c = (a + b);
  if (c >= MOD) c -= MOD;
  return c;
}
int pwr(int a, int b) {
  if (!b) return 1;
  int c = pwr(a, b >> 1);
  c = 1LL * c * c % MOD;
  if (b & 1) c = 1LL * c * a % MOD;
  return c;
}
int inv(int p) { return pwr(p, MOD - 2); }
int main() {
  scanf("%d %d", &n, &c);
  Pwr[0] = 1;
  for (int i = 1; i <= 3000; i++)
    Pwr[i] = add(Pwr[i - 1], Pwr[i - 1]), Inv[i] = inv(Pwr[i] - 1);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  if (c <= LOG) {
    for (int mask = 0; mask < (1 << c); mask++) dp[(n + 1) & 1][0][mask] = 1;
    for (int i = n; i >= 1; i--)
      for (int t = 0; t <= (n - i + 1) / c + 1; t++)
        for (int mask = 0; mask < (1 << c) - 1; mask++) {
          dp[i & 1][t][mask] = dp[(i & 1) ^ 1][t][mask];
          int nw_mask = mask | (1 << (a[i] - 1));
          if (nw_mask == ((1 << c) - 1) && t)
            dp[i & 1][t][mask] =
                add(dp[i & 1][t][mask], dp[(i & 1) ^ 1][t - 1][0]);
          else if (nw_mask != ((1 << c) - 1))
            dp[i & 1][t][mask] =
                add(dp[i & 1][t][mask], dp[(i & 1) ^ 1][t][nw_mask]);
        }
    printf("%d ", add(dp[1][0][0], -1));
    for (int k = 1; k <= n; k++) printf("%d ", dp[1][k][0]);
    return 0;
  } else {
    for (int i = 1; i <= n; i++) {
      memset(ted, 0, sizeof ted);
      int ans = 1, zeroes = c;
      for (int j = i; j <= n; j++) {
        if (a[j] != a[i] && ted[a[j]]) ans = 1LL * ans * Inv[ted[a[j]]] % MOD;
        if (ted[a[j]] == 0) zeroes--;
        ted[a[j]]++;
        if (a[j] != a[i] && ted[a[j]])
          ans = 1LL * ans * (Pwr[ted[a[j]]] - 1) % MOD;
        f[i][j] = ((zeroes > 0) ? 0 : ans);
      }
    }
    for (int i = 0; i <= n; i++) dp2[0][i] = Pwr[i];
    ans[0] = dp2[0][n];
    for (int k = 1; k <= n / c; k++) {
      memset(dp2[k & 1], 0, sizeof dp2[k & 1]);
      for (int j = 1; j <= n; j++)
        for (int i = j; i <= n; i++)
          dp2[k & 1][i] =
              add(dp2[k & 1][i], 1LL * dp2[(k & 1) ^ 1][j - 1] * f[j][i] % MOD);
      ans[k] = dp2[k & 1][n];
    }
    printf("%d ", add(ans[0], add(MOD - ans[1], MOD - 1)));
    for (int k = 1; k <= n / c; k++)
      printf("%d ", add(ans[k], MOD - ans[k + 1]));
    for (int k = n / c + 1; k <= n; k++) printf("%d ", 0);
    return 0;
  }
}
