#include <bits/stdc++.h>
using namespace std;
void solve() {
  long long int n, k, i, amax = -1;
  cin >> n >> k;
  vector<long long int> a(n);
  for (i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort((a).begin(), (a).end());
  long long int ans = 0, currmax = k;
  for (i = 0; i < n; i++) {
    if (a[i] <= 2 * currmax) {
      currmax = max(a[i], currmax);
    } else {
      ans++;
      currmax = 2 * currmax;
      i--;
    }
  }
  cout << ans;
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long int T;
  T = 1;
  while (T--) {
    solve();
  }
}
