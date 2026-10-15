#include <bits/stdc++.h>
using namespace std;
const long long int mod = 1e9 + 7;
const long long int cmod = 998244353;
const long long int N = 1e7 + 2;
const long long int inf = 1e16 + 2;
void solve(long long int ze) {
  long long int n, x, m;
  cin >> n >> x >> m;
  long long int l = x, r = x;
  for (long long int i = 0, a, b; i < m; i++) {
    cin >> a >> b;
    if (a > r or b < l) continue;
    l = min(l, a);
    r = max(r, b);
  }
  cout << r - l + 1 << '\n';
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long int testcase = 1;
  cin >> testcase;
  long long int x = 1;
  while (testcase--) {
    solve(x++);
  }
  return 0;
}
