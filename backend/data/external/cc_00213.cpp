#include <bits/stdc++.h>
using namespace std;
int main() {
  long long x, y, k, n;
  cin >> y >> k >> n;
  int flag = 0;
  for (int i = 1; i < (n / k) + 1; i++) {
    x = i * k - y;
    if (x >= 1) {
      cout << x << " " << endl;
      flag = 1;
    }
  }
  if (flag == 0) {
    cout << -1 << endl;
  }
  return 0;
}
