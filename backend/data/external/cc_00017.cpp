#include <bits/stdc++.h>
using namespace std;
const int N = 111;
struct node {
  int a, b;
  node() {}
  node(int a, int b) : a(a), b(b) {}
} a[N];
int cmp(node a, node b) {
  if (a.b != b.b) return a.b > b.b;
  return a.a > b.a;
}
int dp[2][N][N * N];
int main() {
  int n;
  while (cin >> n) {
    int sa = 0;
    for (int i = 1; i <= n; ++i) cin >> a[i].a, sa += a[i].a;
    for (int i = 1; i <= n; ++i) cin >> a[i].b;
    sort(a + 1, a + 1 + n, cmp);
    int k = 0, sb = 0;
    for (int i = 1; !k && i <= n; ++i) {
      sb += a[i].b;
      if (sb >= sa) k = i;
    }
    memset(dp, -1, sizeof(dp));
    int curb = 0;
    dp[0][0][0] = dp[1][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
      curb += a[i].b;
      for (int j = 1; j <= k; ++j) {
        if (j > i) break;
        for (int w = curb; w >= 0; --w) {
          dp[i & 1][j][w] = dp[1 - (i & 1)][j][w];
          if (w < a[i].b || dp[1 - (i & 1)][j - 1][w - a[i].b] == -1) continue;
          dp[i & 1][j][w] =
              max(dp[1 - (i & 1)][j - 1][w - a[i].b] + a[i].a, dp[i & 1][j][w]);
        }
      }
    }
    int maxi = 0;
    for (int i = sa; i <= curb; ++i) maxi = max(maxi, dp[n & 1][k][i]);
    int t = sa - maxi;
    cout << k << " " << t << endl;
  }
  return 0;
}
