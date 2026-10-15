#include <bits/stdc++.h>
using namespace std;
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
  cerr << name << " : " << arg1 << '\n';
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
  const char* comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << " : " << arg1 << " | ";
  __f(comma + 1, args...);
}
void FASTIO() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
long long dp[55][55][55][55];
long long a[55][55];
long long n;
long long solve(long long x1, long long y1, long long x2, long long y2) {
  long long& ans = dp[x1][y1][x2][y2];
  if (ans != -1) return ans;
  if (x1 == x2 and y1 == y2) {
    return ans = a[x1][y1];
  }
  ans = max(x2 - x1 + 1, y2 - y1 + 1);
  for (long long i = x1; i < x2; i++) {
    ans = min(ans, solve(x1, y1, i, y2) + solve(i + 1, y1, x2, y2));
  }
  for (long long i = y1; i < y2; i++) {
    ans = min(ans, solve(x1, y1, x2, i) + solve(x1, i + 1, x2, y2));
  }
  return ans;
}
void test_case() {
  cin >> n;
  memset(dp, -1, sizeof(dp));
  for (long long i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (long long j = 1; j <= n; j++) {
      a[i][j] = (s[j - 1] == '#') ? 1 : 0;
    }
  }
  cout << solve(1, 1, n, n);
}
int32_t main() {
  FASTIO();
  long long t;
  t = 1;
  for (long long i = 1; i <= t; i++) {
    test_case();
  }
  return 0;
}
