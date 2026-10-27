#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  int a[n];
  long long num[m + 5];
  for (int i = 0; i <= m + 4; i++) num[i] = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    num[a[i]]++;
  }
  long long answer = 0;
  long long dp[m + 5][3][3][3];
  for (int i = 0; i <= m + 4; i++)
    for (int j1 = 0; j1 < 3; j1++)
      for (int j2 = 0; j2 < 3; j2++)
        for (int j3 = 0; j3 < 3; j3++) dp[i][j1][j2][j3] = 0;
  for (int i = 1; i <= m; i++) {
    for (long long j1 = 0; j1 < 3; j1++)
      for (long long j2 = 0; j2 < 3; j2++)
        for (long long j3 = 0; j3 < 3; j3++)
          for (long long j4 = 0; j4 < 3; j4++) {
            if (i == 1) {
              if (j3 + j2 + j1 != 0) continue;
              long long numbleft = num[1] - j4;
              if (numbleft >= 0 && num[2] >= j4 && num[3] >= j4) {
                dp[i][j2][j3][j4] = max(dp[i][j2][j3][j4], j4 + numbleft / 3);
              }
              continue;
            }
            if (i == 2) {
              if (j1 + j2 != 0) continue;
              int numbleft1 = num[1] - j1 - j2 - j3;
              int numbleft2 = num[2] - j2 - j3 - j4;
              int numbleft3 = num[3] - j3 - j4;
              int numbleft4 = num[4] - j4;
              if (numbleft1 >= 0 && numbleft2 >= 0 && numbleft4 >= 0 &&
                  numbleft3 >= 0)
                dp[i][j2][j3][j4] =
                    max(dp[i][j2][j3][j4],
                        dp[i - 1][j1][j2][j3] + numbleft2 / 3 + j4);
              continue;
            }
            if (i == 3) {
              if (j1 != 0) continue;
              int numbleft1 = num[1] - j1 - j2;
              int numbleft2 = num[2] - j1 - j2 - j3;
              int numbleft3 = num[3] - j2 - j3 - j4;
              int numbleft4 = num[4] - j3 - j4;
              int numbleft5 = num[5] - j4;
              if (numbleft1 >= 0 && numbleft2 >= 0 && numbleft3 >= 0 &&
                  numbleft4 >= 0 && numbleft5 >= 0)
                dp[i][j2][j3][j4] =
                    max(dp[i][j2][j3][j4],
                        dp[i - 1][j1][j2][j3] + numbleft3 / 3 + j4);
              continue;
            }
            int numbleft0 = num[i - 3] - j1;
            int numbleft1 = num[i - 2] - j1 - j2;
            int numbleft2 = num[i - 1] - j1 - j2 - j3;
            int numbleft3 = num[i] - j2 - j3 - j4;
            int numbleft4 = num[i + 1] - j3 - j4;
            int numbleft5 = num[i + 2] - j4;
            if (numbleft0 >= 0 && numbleft1 >= 0 && numbleft2 >= 0 &&
                numbleft3 >= 0 && numbleft4 >= 0 && numbleft5 >= 0)
              dp[i][j2][j3][j4] =
                  max(dp[i][j2][j3][j4],
                      dp[i - 1][j1][j2][j3] + numbleft3 / 3 + j4);
          }
  }
  for (int j1 = 0; j1 < 3; j1++)
    for (int j2 = 0; j2 < 3; j2++)
      for (int j3 = 0; j3 < 3; j3++) answer = max(dp[m][j1][j2][j3], answer);
  cout << answer;
  return 0;
}
