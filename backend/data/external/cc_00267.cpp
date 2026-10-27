#include <bits/stdc++.h>
using namespace std;
const int mx = 5005;
int type[mx], dp[mx];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    double x;
    cin >> type[i] >> x;
  }
  for (int i = 1; i <= n; i++) {
    int j = type[i];
    for (int k = j; k >= 1; k--) dp[j] = max(dp[j], 1 + dp[k]);
  }
  int ret = 0;
  for (int i = 1; i <= n; i++) ret = max(ret, dp[i]);
  cout << n - ret << endl;
  return 0;
}
