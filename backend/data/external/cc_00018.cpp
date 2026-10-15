#include <bits/stdc++.h>
using namespace std;
int gcd(int x, int y) {
  if (y == 0) return x;
  return gcd(y, x % y);
}
int lcm(int x, int y) { return x / gcd(x, y) * y; }
int lowbit(int x) { return x & (-x); }
long long quickmod(long long x, long long y, long long mod) {
  x = x % mod;
  long long ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % mod;
    y >>= 1;
    x = x * x % mod;
  }
  return ans;
}
const int INF = 0x3f3f3f3f;
const double EPS = 1e-7;
const double PI = acos(-1.0);
const long long MOD = 1e9 + 7;
int n;
int num1[105], num2[105];
int dp[2][105][20005];
int main() {
  while (scanf("%d", &n) != EOF) {
    memset(dp, -1, sizeof(dp));
    int sum = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &num1[i]);
      sum += num1[i];
    }
    for (int i = 1; i <= n; i++) scanf("%d", &num2[i]);
    dp[0][0][0] = 0;
    int flag = 0;
    for (int i = 1; i <= n; i++) {
      flag ^= 1;
      for (int j = 0; j <= i; j++) {
        for (int k = 0; k <= 20000; k++) {
          dp[flag][j][k] = dp[flag ^ 1][j][k];
          if (j >= 1 && k >= num2[i] && dp[flag ^ 1][j - 1][k - num2[i]] != -1)
            dp[flag][j][k] =
                max(dp[flag][j][k], dp[flag ^ 1][j - 1][k - num2[i]] + num1[i]);
        }
      }
    }
    int ans1 = -1, ans2 = 0;
    for (int j = 1; j <= n; j++) {
      ans2 = 0;
      for (int k = 20000; k >= sum; k--) {
        if (dp[flag][j][k] != -1) {
          ans1 = j;
          ans2 = max(ans2, dp[flag][j][k]);
        }
      }
      if (ans1 != -1) break;
    }
    printf("%d %d\n", ans1, sum - ans2);
  }
  return 0;
}
