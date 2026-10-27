#include <bits/stdc++.h>
using namespace std;
const long long N = 3e3 + 5;
long long dp[N][N], c[N], t[N], n;
long long solve(long long idx, long long tot) {
  if (idx == 0) {
    if (tot >= n) return 0;
    return 1e15;
  }
  if (tot >= n) return 0;
  long long &ans = dp[idx][tot];
  if (ans != -1) return ans;
  long long take = solve(idx - 1, tot + t[idx]) + c[idx];
  long long leave = solve(idx - 1, tot);
  ans = min(take, leave);
  return ans;
}
signed main() {
  std ::ios_base ::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ;
  cin >> n;
  for (long long i = 1; i <= n; i++) {
    cin >> t[i] >> c[i];
    t[i]++;
  }
  for (long long i = 0; i < N; i++)
    for (long long j = 0; j < N; j++) dp[i][j] = -1;
  cout << solve(n, 0);
}
