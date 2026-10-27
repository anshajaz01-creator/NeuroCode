#include <bits/stdc++.h>
using namespace std;
long long a, b, x, y;
bool chk(long long mid) {
  long long num = mid / x;
  long long f = mid - num;
  num = mid / y;
  long long s = mid - num;
  return a <= f && b <= s && mid - (mid / (x * y)) >= a + b;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> a >> b >> x >> y;
  long long st = a + b, ed = 1e12;
  while (st < ed) {
    long long mid = (st + ed) / 2;
    if (chk(mid))
      ed = mid;
    else
      st = mid + 1;
  }
  cout << ed;
}
