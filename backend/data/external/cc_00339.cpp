#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;
const int maxm = 101010;
const int maxk = 15;
const long long inf = 0x3f3f3f3f3f3f3f3f;
int n, k;
long long h[maxk];
long long dp[maxn][maxn * maxk];
long long solve(int res, int val) {
  if (res == 0 or val == 0) return 0ll;
  if (dp[res][val] >= 0) return dp[res][val];
  dp[res][val] = 0;
  for (int i = 1; i <= min(val, k); i++)
    dp[res][val] = max(dp[res][val], solve(res - 1, val - i) + h[i]);
  return dp[res][val];
}
int cnt[maxm], g[maxm];
int main() {
  ios_base::sync_with_stdio(false), cin.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n * k; i++) {
    int x;
    cin >> x;
    cnt[x]++;
  }
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    g[x]++;
  }
  for (int i = 1; i <= k; i++) cin >> h[i];
  long long ans = 0;
  for (int i = 1; i <= 100000; i++) {
    if (cnt[i] and g[i]) {
      for (int j = 0; j <= g[i]; j++)
        for (int k = 0; k <= cnt[i]; k++) dp[j][k] = -1;
      long long x = solve(g[i], cnt[i]);
      ans += x;
    }
  }
  cout << ans << "\n";
}
