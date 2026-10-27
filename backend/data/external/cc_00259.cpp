#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
int dp[N][27];
int can[27][27];
int main() {
  ios::sync_with_stdio(false);
  string str;
  cin >> str;
  int n = str.size();
  int k;
  cin >> k;
  for (int i = 0; i <= 'z' - 'a'; i++) {
    for (int j = 0; j <= 'z' - 'a'; j++) {
      can[i][j] = 1;
    }
  }
  while (k--) {
    string x;
    cin >> x;
    can[x[0] - 'a'][x[1] - 'a'] = 0;
    can[x[1] - 'a'][x[0] - 'a'] = 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int c = 0; c <= 'z' - 'a'; c++) {
      dp[i][c] = int(1e9);
    }
    dp[i][str[i - 1] - 'a'] = i - 1;
    if (i - 1 > 0)
      for (int c = 0; c <= 'z' - 'a'; c++) {
        dp[i][c] = min(dp[i][c], dp[i - 1][c] + 1);
        if (can[c][str[i - 1] - 'a'])
          dp[i][str[i - 1] - 'a'] = min(dp[i][str[i - 1] - 'a'], dp[i - 1][c]);
      }
  }
  int ans = int(1e9);
  for (int c = 0; c <= 'z' - 'a'; c++) {
    ans = min(ans, dp[n][c]);
  }
  cout << ans << '\n';
  return 0;
}
