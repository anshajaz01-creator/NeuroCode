#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int i, j, k, m, n, p, t;
  cin >> n >> m;
  long long int x[n], y[n];
  long long int f = 0;
  for (i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  if (x[0] != 0) {
    cout << "NO\n";
    return 0;
  }
  long long int rt = y[0];
  if (rt >= m) {
    cout << "YES\n";
    return 0;
  }
  for (i = 1; i < n; i++) {
    if (x[i] > rt) {
      cout << "NO\n";
      return 0;
    }
    rt = max(rt, y[i]);
    if (rt >= m) {
      cout << "YES\n";
      return 0;
    }
  }
  cout << "NO\n";
  return 0;
}
