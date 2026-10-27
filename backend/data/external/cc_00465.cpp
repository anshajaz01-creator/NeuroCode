#include <bits/stdc++.h>
using namespace std;
int n, k, a[105], b[105], dp[105][20005];
int main() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
  }
  memset(dp, -1, sizeof(dp));
  for (int i = 0; i <= n; i++) dp[i][10000] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = k * b[i] - a[i]; j <= 20000; j++) {
      if (dp[i - 1][j - k * b[i] + a[i]] == -1) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - k * b[i] + a[i]] + a[i]);
      }
    }
  }
  printf("%d", dp[n][10000] == 0 ? -1 : dp[n][10000]);
  return 0;
}
