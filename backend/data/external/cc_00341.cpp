#include <bits/stdc++.h>
using namespace std;
template <typename A, typename B>
ostream& operator<<(ostream& o, pair<A, B> a) {
  return o << a.first << ' ' << a.second;
}
template <typename A, typename B>
istream& operator>>(istream& o, pair<A, B>& a) {
  return o >> a.first >> a.second;
}
const int mod = 998244353, abc = 864197532, N = 200005, K = 111;
int dp[5001][501];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> cnt1(100001, 0), cnt2(100001, 0), h(k + 1, 0);
  for (int i = 0, x; i < n * k; ++i) cin >> x, cnt1[x]++;
  for (int i = 0, x; i < n; ++i) cin >> x, cnt2[x]++;
  for (int i = 0; i < k; ++i) cin >> h[i + 1];
  for (int i = 0; i <= n * k; ++i) {
    for (int j = 0; j <= n; ++j) {
      dp[i][j] = -1 << 30;
    }
  }
  dp[0][0] = 0;
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < n * k; ++i) {
      for (int cnt = 0; cnt <= k; ++cnt)
        if (i + cnt <= n * k) {
          dp[i + cnt][j + 1] = max(dp[i + cnt][j + 1], dp[i][j] + h[cnt]);
        }
    }
  }
  int ans = 0;
  for (int i = 1; i <= 100000; ++i)
    if (cnt2[i] > 0) {
      cnt1[i] = min(cnt1[i], cnt2[i] * k);
      ans += dp[cnt1[i]][cnt2[i]];
    }
  cout << ans << endl;
}
