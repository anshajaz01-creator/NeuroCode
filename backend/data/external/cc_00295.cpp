#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n, a[100010], dp[100010][205][2], b[205][2];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= 200; i++)
    if (a[1] == i || a[1] == -1) dp[1][i][0] = 1;
  for (int i = 2; i <= n; i++) {
    b[0][0] = 0;
    b[0][1] = 0;
    for (int j = 1; j <= 200; j++) {
      b[j][0] = (b[j - 1][0] + dp[i - 1][j][0]) % mod;
      b[j][1] = (b[j - 1][1] + dp[i - 1][j][1]) % mod;
    }
    for (int j = 1; j <= 200; j++) {
      if (a[i] != -1 && a[i] != j) continue;
      dp[i][j][0] = (dp[i][j][0] + b[j - 1][0]) % mod;
      dp[i][j][0] = (dp[i][j][0] + b[j - 1][1]) % mod;
      dp[i][j][1] = (dp[i][j][1] + b[200][1]) % mod;
      dp[i][j][1] = (dp[i][j][1] - b[j - 1][1] + mod) % mod;
      dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j][0]) % mod;
    }
  }
  int ans = 0;
  for (int i = 1; i <= 200; i++) ans = (ans + dp[n][i][1]) % mod;
  printf("%d\n", ans);
  return 0;
}
