#include <bits/stdc++.h>
using namespace std;
long long n = 0;
long long sol(long long tc) {
  long long y, k;
  cin >> y >> k;
  cin >> n;
  if (y >= n) {
    cout << -1;
  } else {
    long long num = k - y % k;
    if (num + y <= n) {
      while (num + y <= n) {
        cout << num << " ";
        num += k;
      }
    } else
      cout << -1;
  }
  cout << endl;
  return 0LL;
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long tc = 1;
  while (tc--) {
    sol(tc);
  }
  return 0;
}
