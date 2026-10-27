#include <bits/stdc++.h>
using namespace std;
int c[1002], n, m, d, q, p, k, j;
int main() {
  cin >> n >> m >> d;
  q = d - 1, p = m + 1;
  for (int i = 1; i <= m; i++) cin >> c[i], n -= c[i];
  if (n > p * q)
    cout << "NO\n";
  else {
    cout << "YES" << endl;
    for (int i = 0; i <= m; i++) {
      for (int j = 0; j < c[i]; j++) cout << i << ' ';
      for (k = min(n, q), n -= k, j = 0; j < k; j++) cout << 0 << ' ';
    }
  }
  return 0;
}
