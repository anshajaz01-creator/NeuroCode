#include <bits/stdc++.h>
using namespace std;
long long int x, y, z, a, b, ans;
int main() {
  ios::sync_with_stdio(false);
  cin >> x >> y >> z;
  ans = x / z + y / z;
  a = x % z;
  b = y % z;
  if (a > b) {
    if (z - a <= b) {
      cout << ans + 1 << " " << z - a;
    } else {
      cout << ans << " 0";
    }
  } else {
    if (z - b <= a) {
      cout << ans + 1 << " " << z - b;
    } else {
      cout << ans << " 0";
    }
  }
  return 0;
}
