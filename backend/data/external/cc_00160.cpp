#include <bits/stdc++.h>
using namespace std;
template <typename T>
void out(T x) {
  cout << x << endl;
  exit(0);
}
void relax(int &x, int y) { x = max(x, y); }
const int inf = 1e9;
int n, k;
int dp[20][1 << 18][2][2];
int like[1 << 18];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i <= n + 1; i++) {
    for (int j = 0; j < 1 << n; j++) {
      for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
          dp[i][j][a][b] = -inf;
        }
      }
    }
  }
  while (k--) {
    int i;
    cin >> i;
    --i;
    like[i] = 1;
  }
  for (int i = 0; i < 1 << n; i += 2) {
    for (int a = 0; a < 2; a++) {
      for (int b = 0; b < 2; b++) {
        if (like[i] + like[i + 1] == a + b) {
          relax(dp[1][i][a][b], a || b);
        }
      }
    }
  }
  for (int d = 2; d <= n; d++) {
    for (int i = 0; i < 1 << n; i += (1 << d)) {
      int j = i + (1 << (d - 1));
      for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
          if (dp[d - 1][i][a][b] >= 0) {
            for (int x = 0; x < 2; x++) {
              for (int y = 0; y < 2; y++) {
                if (dp[d - 1][j][x][y] >= 0) {
                  bool ub = (a || x);
                  bool lb = (b || y);
                  bool lb2 = (a && x) || lb;
                  relax(dp[d][i][ub][lb], ub + lb + lb2 + dp[d - 1][i][a][b] +
                                              dp[d - 1][j][x][y]);
                }
              }
            }
          }
        }
      }
    }
  }
  int res = 0;
  for (int a = 0; a < 2; a++) {
    for (int b = 0; b < 2; b++) {
      relax(res, dp[n][0][a][b] + (a || b));
    }
  }
  out(res);
  return 0;
}
