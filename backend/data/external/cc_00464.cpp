#include <bits/stdc++.h>
using namespace std;
int a[101], b[101], dp[2][101][10001], n;
int foo(int sgn, int pos, int dif) {
  if (dif > 10000) return -1e9;
  if (pos < 0 && dif == 0) return 0;
  if (pos < 0) return -1e9;
  int &ans = dp[sgn][pos][dif];
  if (ans == -1) {
    ans = 0;
    int sum_a = dif * ((sgn == 1) ? -1 : 1);
    ans = max(ans, foo(sgn, pos - 1, dif));
    if (sum_a + (a[pos] - b[pos]) < 0)
      ans =
          max(ans, a[pos] + foo(1, pos - 1, (sum_a + a[pos] - b[pos]) * (-1)));
    else
      ans = max(ans, a[pos] + foo(0, pos - 1, (sum_a + a[pos] - b[pos])));
  }
  if (ans == 0 && dif == 0)
    return 0;
  else if (ans == 0)
    return -1e9;
  return ans;
}
int main() {
  ios_base ::sync_with_stdio(0);
  cin.tie(0);
  for (int j = 0; j < 101; j++)
    for (int k = 0; k < 10001; k++)
      for (int i = 0; i < 2; i++) dp[i][j][k] = -1;
  int k;
  cin >> n >> k;
  for (int j = 0; j < n; j++) cin >> a[j];
  for (int j = 0; j < n; j++) cin >> b[j], b[j] *= k;
  int ans = foo(0, n - 1, 0);
  if (ans == 0) ans = -1;
  cout << ans << endl;
  return 0;
}
