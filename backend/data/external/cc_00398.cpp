#include <bits/stdc++.h>
using namespace std;
long long n, st, en, m;
bool ok(long long mid) {
  long long l;
  l = (m + 1 + (m - mid)) * (mid) / 2;
  return l - (mid - 1) >= n;
}
int main() {
  cin >> n >> m;
  st = 1, en = m;
  if (n == 1) {
    cout << 0;
    return 0;
  }
  if (m >= n) {
    cout << 1;
    return 0;
  }
  long long mid;
  while (st <= en) {
    mid = (st + en) / 2;
    if (st == en) break;
    if (ok(mid))
      en = mid;
    else
      st = mid + 1;
  }
  if (st >= m)
    cout << -1;
  else
    cout << en;
}
