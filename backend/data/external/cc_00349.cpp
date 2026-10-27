#include <bits/stdc++.h>
using namespace std;
#pragma optimize("O3")
const long long N = 2e5 + 5, mod = 1e9 + 7, inf = 1e9 + 7;
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long a, b, c;
  cin >> a >> b >> c;
  cout << (a + b) / c << ' ';
  if (a % c + b % c < c) return cout << 0, 0;
  ;
  cout << min(min(a % c, c - a % c), min(b % c, c - b % c));
}
