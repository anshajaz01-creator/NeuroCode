#include <bits/stdc++.h>
using namespace std;
const int N = int(4e5) + 5;
const int inf = (int)1e9 + 9;
int n;
int a[3][N];
long long ret[N], s[3][N], ret2[N];
long long sum(int i, int l, int r) { return s[i][r] - s[i][l - 1]; }
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= 2; ++i) {
    for (int j = 1; j <= n; ++j) {
      scanf("%d", &a[i][j]);
      s[i][j] = s[i][j - 1] + a[i][j];
    }
  }
  long long ans = 0, now = 0;
  ret[n] = a[2][n];
  for (int i = n - 1; i >= 1; --i) {
    ret[i] = ret[i + 1] + sum(1, i + 1, n) + sum(2, i + 1, n) +
             a[2][i] * 1ll * ((n - i + 1) * 2 - 1);
  }
  ret2[n] = a[1][n];
  for (int i = n - 1; i >= 1; --i) {
    ret2[i] = ret2[i + 1] + sum(1, i + 1, n) + sum(2, i + 1, n) +
              a[1][i] * 1ll * ((n - i + 1) * 2 - 1);
  }
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    if (i % 2) {
      ans = max(ans, now + ret[i] + sum(1, i, n) * 1ll * (2 * (i - 1)) +
                         sum(2, i, n) * 1ll * (2 * (i - 1)));
    } else {
      ans = max(ans, now + ret2[i] + sum(1, i, n) * 1ll * (2 * (i - 1)) +
                         sum(2, i, n) * 1ll * (2 * (i - 1)));
    }
    if (i % 2) {
      now += a[1][i] * 1ll * cnt;
      ++cnt;
      now += a[2][i] * 1ll * cnt;
      ++cnt;
    } else {
      now += a[2][i] * 1ll * cnt;
      ++cnt;
      now += a[1][i] * 1ll * cnt;
      ++cnt;
    }
  }
  ans = max(ans, now);
  printf("%lld", ans);
  return 0;
}
