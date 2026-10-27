#include <bits/stdc++.h>
using namespace std;
const long long inf = (1ll << 60);
long long dp[2005][2005], sum;
int n, c[2005], t[2005];
int main() {
  scanf("%d", &n);
  sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", t + i, c + i);
    sum += c[i];
    t[i]++;
  }
  for (int i = 1; i <= n; i++) dp[0][i] = inf;
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= n; j++) {
      dp[i][j] = min(dp[i - 1][j], dp[i - 1][max(0, j - t[i])] + c[i]);
    }
  printf("%I64d\n", dp[n][n]);
  return 0;
}
