#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
long long n, t[2010], c[2010], ans = 1e18, res = 0;
long long dp[4010];
int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> t[i] >> c[i], res += c[i];
  for (int i = 0; i < 4005; i++) dp[i] = 1e18;
  dp[t[0] + 1] = c[0];
  dp[0] = 0;
  for (int i = 1; i <= n - 1; i++) {
    for (int j = 4000; j >= 1; j--) {
      if (j - t[i] - 1 >= 0) dp[j] = min(dp[j], dp[j - t[i] - 1] + c[i]);
    }
  }
  for (int j = 1; j <= 4000; j++)
    if (j >= n) ans = min(ans, dp[j]);
  cout << min(ans, res) << endl;
  return 0;
}
