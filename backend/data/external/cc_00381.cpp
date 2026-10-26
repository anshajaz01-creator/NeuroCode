#include <bits/stdc++.h>
using namespace std;
template <class TH>
void _dbg(const char *sdbg, TH h) {
  cerr << sdbg << " = " << h << endl;
}
template <class TH, class... TA>
void _dbg(const char *sdbg, TH h, TA... a) {
  while (*sdbg != ',') cerr << *sdbg++;
  cerr << " = " << h << ", ";
  _dbg(sdbg + 1, a...);
}
const int maxn = (1e6) + 7;
const int maxk = 20;
const int inf = (1e9) + 7;
const long long LLinf = (1e18) + 7;
const long double eps = 1e-9;
const long long mod = 1e9 + 7;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long n, m;
  cin >> n >> m;
  long long cur = m;
  for (int i = 1; i <= n; i++) {
    long long ile;
    cin >> ile;
    if (ile < cur) {
      cur -= ile;
      cout << "0 ";
    } else {
      ile -= cur;
      long long res = 1 + ile / m;
      cur = m - ile % m;
      cout << res << " ";
    }
  }
  return 0;
}
