#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n;
  cin >> n;
  long long a[n], b[n];
  for (long long i = 0; i < n; i++) cin >> a[i];
  for (long long i = 0; i < n; i++) cin >> b[i];
  long long dp[n][2][2];
  memset(dp, 0, sizeof(dp));
  dp[n - 1][0][0] = b[n - 1];
  dp[n - 1][1][0] = b[n - 1];
  dp[n - 1][0][1] = a[n - 1];
  dp[n - 1][1][1] = a[n - 1];
  long long sum = a[n - 1] + b[n - 1];
  long long done = 2;
  for (long long i = n - 2; i >= 0; i--) {
    dp[i][0][0] = max(dp[i + 1][0][1], dp[i + 1][1][1]) + 2 * sum + b[i];
    dp[i][1][0] = dp[i + 1][1][0] + sum + b[i] * (done + 1);
    dp[i][0][1] = max(dp[i + 1][0][0], dp[i + 1][1][0]) + 2 * sum + a[i];
    dp[i][1][1] = dp[i + 1][1][1] + sum + a[i] * (done + 1);
    sum += (a[i] + b[i]);
    done += 2;
  }
  long long ans = 0;
  for (long long i = 0; i < 2; i++) {
    ans = max(ans, dp[0][i][0]);
  }
  cout << ans << "\n";
  return 0;
}
