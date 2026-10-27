#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m, s = 0, x;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> x;
    s += x;
    cout << (s / m) << " ";
    s = s % m;
  }
  return 0;
}
