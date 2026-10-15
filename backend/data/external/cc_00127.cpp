#include <bits/stdc++.h>
using namespace std;
const long long maxN = 2005;
const long long inf = 10000000000000;
struct item {
  long long t;
  long long c;
};
long long dp[maxN][maxN];
item col[maxN + 1];
long long DP(long long n, long long T) {
  if (T <= 0) return 0;
  if (n <= 0) return inf;
  if (dp[n][T] != -1) return dp[n][T];
  long long ret = inf;
  ret = min(ret, col[n].c + DP(n - 1, T - col[n].t));
  ret = min(ret, DP(n - 1, T));
  return dp[n][T] = ret;
}
signed main() {
  long long N;
  cin >> N;
  long long i, j, k;
  for (i = 1; i <= N; i++) {
    cin >> col[i].t >> col[i].c;
    col[i].t++;
  }
  for (i = 1; i <= N; i++) {
    for (j = 1; j <= N; j++) {
      dp[i][j] = -1;
    }
  }
  long long ans = DP(N, N);
  printf("%lld\n", ans);
}
