#include <bits/stdc++.h>
using namespace std;
bool solve(long long n, long long x, long long y, long long cnt1,
           long long cnt2) {
  long long p, q, r;
  p = n / x - n / (x * y);
  q = n / y - n / (x * y);
  r = n - (n / x + n / y - n / (x * y));
  return (max(0LL, cnt1 - q) + max(0LL, cnt2 - p) <= r);
}
int main() {
  long long x, y, lo, mid, hi, cnt1, cnt2;
  int k, i, j;
  string s;
  cin >> cnt1 >> cnt2 >> x >> y;
  lo = 0LL;
  hi = 1000000000000000000LL;
  for (k = 0; k < 100; k++) {
    mid = (lo + hi) / 2LL;
    if (solve(mid, x, y, cnt1, cnt2)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  for (i = mid;; i++) {
    if (solve(i, x, y, cnt1, cnt2)) {
      cout << i << "\n";
      break;
    }
  }
  return 0;
}
