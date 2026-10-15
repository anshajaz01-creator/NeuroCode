#include <bits/stdc++.h>
using namespace std;
const int maxn = 805;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
char s[maxn];
bool ok(int x, int y) { return x == 0 && y != 0 || x != 0 && y == 0; }
int sta[maxn];
int p[maxn];
long long dp[maxn][maxn][3][3];
void sol(int l, int r) {
  if (l + 1 == r) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) dp[l][r][i][j] = ok(i, j);
    return;
  }
  if (p[l] == r) {
    sol(l + 1, r - 1);
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        if (!ok(i, j)) continue;
        for (int k = 0; k < 3; k++)
          for (int h = 0; h < 3; h++) {
            if (i > 0 && i == k || h > 0 && h == j) continue;
            dp[l][r][i][j] += dp[l + 1][r - 1][k][h];
          }
        dp[l][r][i][j] %= mod;
      }
  } else {
    int r1 = p[l];
    sol(l, r1);
    sol(r1 + 1, r);
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++)
          for (int h = 0; h < 3; h++) {
            if (k > 0 && k == h) continue;
            dp[l][r][i][j] += dp[l][r1][i][k] * dp[r1 + 1][r][h][j] % mod;
          }
        dp[l][r][i][j] %= mod;
      }
  }
}
int main() {
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  int top = 0;
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(')
      sta[++top] = i;
    else {
      p[sta[top]] = i;
      top--;
    }
  }
  sol(1, n);
  long long ans = 0;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      ans += dp[1][n][i][j];
    }
  ans %= mod;
  printf("%lld\n", ans);
  return 0;
}
