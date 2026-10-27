#include <bits/stdc++.h>
using namespace std;
char str[750];
long long dp[750][750][3][3], mod = 1e9 + 7;
int n, match[750];
stack<int> zhan;
void DFS(int l, int r) {
  if (l + 1 == r)
    dp[l][r][0][1] = dp[l][r][1][0] = dp[l][r][0][2] = dp[l][r][2][0] = 1;
  else if (match[l] == r) {
    DFS(l + 1, r - 1);
    for (int i = 0; i <= 2; ++i) {
      for (int j = 0; j <= 2; ++j) {
        if (j != 1)
          dp[l][r][0][1] = (dp[l][r][0][1] + dp[l + 1][r - 1][i][j]) % mod;
        if (j != 2)
          dp[l][r][0][2] = (dp[l][r][0][2] + dp[l + 1][r - 1][i][j]) % mod;
        if (i != 1)
          dp[l][r][1][0] = (dp[l][r][1][0] + dp[l + 1][r - 1][i][j]) % mod;
        if (i != 2)
          dp[l][r][2][0] = (dp[l][r][2][0] + dp[l + 1][r - 1][i][j]) % mod;
      }
    }
  } else if (match[l] != r) {
    DFS(l, match[l]), DFS(match[l] + 1, r);
    for (int i = 0; i <= 2; ++i) {
      for (int j = 0; j <= 2; ++j) {
        for (int x = 0; x <= 2; ++x) {
          for (int y = 0; y <= 2; ++y) {
            if ((j == 1 && x == 1) || (j == 2 && x == 2)) continue;
            dp[l][r][i][y] = (dp[l][r][i][y] + dp[l][match[l]][i][j] *
                                                   dp[match[l] + 1][r][x][y]) %
                             mod;
          }
        }
      }
    }
  }
}
int main() {
  scanf("%s", str);
  n = strlen(str);
  for (int i = 0; i < n; ++i) {
    if (str[i] == '(')
      zhan.push(i);
    else {
      match[zhan.top()] = i;
      match[i] = zhan.top();
      zhan.pop();
    }
  }
  DFS(0, n - 1);
  long long ans = 0;
  for (int i = 0; i <= 2; ++i)
    for (int j = 0; j <= 2; ++j) ans = (ans + dp[0][n - 1][i][j]) % mod;
  printf("%lld\n", ans);
  return 0;
}
