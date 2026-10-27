#include <bits/stdc++.h>
using namespace std;
const double PI = atan(1.0) * 4;
const long long int INF = 1e7 + 9;
int dp[52][52][52][52] = {0};
int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n + 1; i++)
    for (int j = 1; j < n + 1; j++) {
      char c;
      cin >> c;
      if (c == '#')
        dp[i][j][i][j] = 1;
      else
        dp[i][j][i][j] = 0;
    }
  for (int r = 0; r < n + 1; r++)
    for (int c = 0; c < n + 1; c++) {
      if (!(r | c)) continue;
      for (int i = 1; i < n + 1; i++)
        for (int j = 1; j < n + 1; j++) {
          int x = i + r;
          int y = j + c;
          if (x > n || y > n) continue;
          int min1 = 1e9;
          for (int p = i; p < x; p++)
            min1 = min(min1, dp[i][j][p][y] + dp[p + 1][j][x][y]);
          for (int q = j; q < y; q++)
            min1 = min(min1, dp[i][j][x][q] + dp[i][q + 1][x][y]);
          dp[i][j][x][y] = min(min1, max(r + 1, c + 1));
        }
    }
  cout << dp[1][1][n][n] << '\n';
  return 0;
}
