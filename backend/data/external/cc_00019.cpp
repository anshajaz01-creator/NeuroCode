#include <bits/stdc++.h>
using namespace std;
int n;
int a[205], b[205], sum;
const int W = 10010;
int dp[205][10500];
int C[205][10500];
int main() {
  int i, j;
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
    sum += b[i];
  }
  for (i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for (i = 0; i <= W; i++) dp[0][i] = W * 10;
  dp[0][0] = 0;
  for (i = 1; i <= n; i++) {
    for (j = 0; j <= W; j++)
      if (j >= a[i]) {
        if (dp[i - 1][j] == dp[i - 1][j - a[i]] + 1) {
          dp[i][j] = dp[i - 1][j];
          C[i][j] = max(C[i - 1][j], C[i - 1][j - a[i]] + b[i]);
          continue;
        }
        if (dp[i - 1][j] > dp[i - 1][j - a[i]] + 1) {
          dp[i][j] = dp[i - 1][j - a[i]] + 1;
          C[i][j] = C[i - 1][j - a[i]] + b[i];
        } else {
          dp[i][j] = dp[i - 1][j];
          C[i][j] = C[i - 1][j];
        }
      } else {
        dp[i][j] = dp[i - 1][j];
        C[i][j] = C[i - 1][j];
      }
  }
  int ans = n + 3, val = 0;
  for (i = sum; i <= W; i++)
    if (dp[n][i] < ans && dp[n][i] != 0) {
      ans = dp[n][i];
      val = C[n][i];
    } else if (dp[n][i] == ans)
      val = max(val, C[n][i]);
  printf("%d %d\n", ans, sum - val);
  return 0;
}
