#include <bits/stdc++.h>
using namespace std;
const long long llinf = 2e18 + 7;
const int inf = 2e9 + 7;
const long long mod = 1e9 + 7;
const long long N = 1e6 + 7;
const long double pi = 3.14159265358979;
bool intersection(long long x1, long long y1, long long x2, long long y2) {
  long long minn = max(x1, x2);
  long long maxx = min(y1, y2);
  if (minn <= maxx) return 1;
  return 0;
}
void solve() {
  long long n, x, m, a, b;
  cin >> n >> x >> m;
  x--;
  long long lb = x, ub = x;
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    a--;
    b--;
    if (intersection(lb, ub, a, b)) {
      lb = min(lb, a);
      ub = max(ub, b);
    }
  }
  cout << ub - lb + 1;
}
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t;
  t = 1;
  cin >> t;
  while (t--) {
    solve();
    cout << "\n";
  }
  return 0;
}
