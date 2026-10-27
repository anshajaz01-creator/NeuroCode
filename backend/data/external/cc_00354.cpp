#include <bits/stdc++.h>
using namespace std;
long long dp[52][52][52][52], sum[55][55];
char s[55][55];
long long f(long long a, long long b, long long c, long long d) {
  long long mn = max(c - a, d - b) + 1, i, j;
  j = sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1];
  if (c < a || d < b) return 0;
  if (a == c || b == d || !j) return j;
  if (dp[a][b][c][d] != -1) return dp[a][b][c][d];
  if (d - b >= c - a)
    for (i = b; i <= d; i++) {
      mn = min(mn, f(a, b, c, i - 1) + f(a, i + 1, c, d) + sum[c][i] -
                       sum[a - 1][i] - sum[c][i - 1] + sum[a - 1][i - 1]);
    }
  else
    for (i = a; i <= c; i++) {
      mn = min(mn, f(a, b, i - 1, d) + f(i + 1, b, c, d) + sum[i][d] -
                       sum[i - 1][d] - sum[i][b - 1] + sum[i - 1][b - 1]);
    }
  dp[a][b][c][d] = mn;
  return mn;
}
int main() {
  {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
  };
  long long i, j, k, l, n, m, h, mod = 998244353, cnt, mx = 1e10, t, ans = 0;
  cin >> n;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      cin >> s[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
      if (s[i][j] == '#') sum[i][j]++;
    }
  }
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      for (l = 1; l <= n; l++)
        for (h = 1; h <= n; h++) dp[i][j][l][h] = -1;
  ans = f(1, 1, n, n);
  cout << ans << endl;
  return 0;
}
