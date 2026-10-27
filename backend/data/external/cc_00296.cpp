#include <bits/stdc++.h>
using namespace std;
template <class T>
using min_heap = priority_queue<T, std::vector<T>, std::greater<T> >;
const int lim = 1e5 + 5;
long long dp[202][3], s[202][3];
long long n, a[lim], ans = 0, MOD = 998244353;
void mymod(long long &x) {
  x %= MOD;
  x += MOD;
  x %= MOD;
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int k = 1; k <= 200; k++) {
    if (a[1] == -1 || a[1] == k) {
      dp[k][1] = 1;
    }
    s[k][1] = s[k - 1][1] + dp[k][1];
  }
  for (int i = 2; i <= n; i++) {
    for (int k = 1; k <= 200; k++) {
      if (a[i] == -1 || a[i] == k) {
        dp[k][0] = dp[k][0] + dp[k][1] + s[200][0] - s[k][0];
        mymod(dp[k][0]);
        dp[k][1] = s[k - 1][0] + s[k - 1][1];
        mymod(dp[k][1]);
      } else {
        dp[k][0] = 0;
        dp[k][1] = 0;
      }
    }
    for (int k = 1; k <= 200; k++) {
      s[k][0] = s[k - 1][0] + dp[k][0];
      mymod(s[k][0]);
      s[k][1] = s[k - 1][1] + dp[k][1];
      mymod(s[k][1]);
    }
  }
  ans = s[200][0];
  ans %= MOD;
  cout << ans << endl;
}
