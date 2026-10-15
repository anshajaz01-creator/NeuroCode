#include <bits/stdc++.h>
using namespace std;
long long cnt1, cnt2, x, y;
long long calc(long long num, long long x) {
  return num / x * (x - 1) + num % x;
}
long long calc2(long long num, long long x, long long y) {
  return num / y - num / (x * y);
}
bool available(long long num) {
  long long both = calc(num, x) + calc(num, y) - calc(num, x * y);
  long long onlyX = calc2(num, x, y);
  long long onlyY = calc2(num, y, x);
  long long remain1 = max(cnt1 - onlyX, 0ll);
  long long remain2 = max(cnt2 - onlyY, 0ll);
  if (remain1 + remain2 <= both) {
    return true;
  }
  return false;
}
int main() {
  cin >> cnt1 >> cnt2 >> x >> y;
  long long low = 1, high = cnt1 * x + cnt2 * y;
  while (low <= high) {
    long long mid = (low + high) / 2;
    if (available(mid)) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  cout << low << endl;
  return 0;
}
