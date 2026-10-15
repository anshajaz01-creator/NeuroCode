#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m, r = 0;
  cin >> n >> m;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  for (int i = 0; i < n; i++) {
    r += v[i];
    if (r >= m) {
      cout << r / m << " ";
      r %= m;
    } else
      cout << 0 << " ";
  }
  return 0;
}
