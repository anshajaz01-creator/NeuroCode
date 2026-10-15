#include <bits/stdc++.h>
using namespace std;
int main() {
  int y, k, n;
  cin >> y >> k >> n;
  bool done = false;
  for (int i = y / k + 1; k * i <= n; i++) {
    cout << k * i - y << ' ';
    done = true;
  }
  if (!done) cout << -1;
  return 0;
}
