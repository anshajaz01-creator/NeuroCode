#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
int GM(int Num) { return (Num < 0 ? Num + MOD : Num % MOD); }
int N, M;
int A[100005];
int dp[2][205][100005];
int Solve() {
  for (int b = 1; b <= 200; b++) dp[1][b][N] = dp[1][b - 1][N] + 1;
  for (int i = N - 1; i; i--) {
    for (int b = 1; b <= 200; b++) {
      if (~A[i] && A[i] < b)
        dp[0][b][i] = 0;
      else if (A[i] == -1)
        dp[0][b][i] = GM(GM(dp[1][b][i + 1] - dp[1][b - 1][i + 1]) +
                         GM(dp[0][200][i + 1] - dp[0][b][i + 1]));
      else
        dp[0][b][i] =
            GM(dp[A[i] == b][A[i]][i + 1] - dp[A[i] == b][A[i] - 1][i + 1]);
      dp[0][b][i] = GM(dp[0][b][i] + dp[0][b - 1][i]);
      if (~A[i])
        dp[1][b][i] =
            GM(dp[A[i] <= b][A[i]][i + 1] - dp[A[i] <= b][A[i] - 1][i + 1]);
      else
        dp[1][b][i] = GM(GM(dp[1][b][i + 1] - dp[1][0][i + 1]) +
                         GM(dp[0][200][i + 1] - dp[0][b][i + 1]));
      dp[1][b][i] = GM(dp[1][b][i] + dp[1][b - 1][i]);
    }
  }
  return (~A[0] ? GM(dp[0][A[0]][1] - dp[0][A[0] - 1][1]) : dp[0][200][1]);
}
int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) scanf("%d", &A[i]);
  printf("%d\n", Solve());
}
