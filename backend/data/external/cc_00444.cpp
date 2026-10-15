#include <bits/stdc++.h>
using namespace std;
vector<long long int> a, b;
int main() {
  long long int ii, i, j, k, n, m, z = 0, c = 0, t, x, y, l, r, mid, u, v, d;
  cin >> n >> m >> d >> t >> v;
  for (i = 0; i < d; i++) {
    cin >> x;
    a.push_back(x);
  }
  for (i = 0; i < t; i++) {
    cin >> x;
    b.push_back(x);
  }
  cin >> l;
  while (l--) {
    long long int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x = lower_bound(a.begin(), a.end(), y1) - a.begin();
    y = lower_bound(b.begin(), b.end(), y1) - b.begin();
    if (x == d) x--;
    if (y == t) y--;
    c = 1999999999;
    r = abs(y1 - y2);
    if (d) c = abs(a[x] - y1) + abs(x2 - x1) + abs(a[x] - y2);
    x--;
    if (x < 0) x = 0;
    if (d) c = min(c, abs(a[x] - y1) + abs(x2 - x1) + abs(a[x] - y2));
    z = (abs(x2 - x1) + v - 1) / v;
    if (t) c = min(c, abs(b[y] - y1) + abs(b[y] - y2) + z);
    y--;
    if (y < 0) y = 0;
    if (t) c = min(c, abs(b[y] - y1) + abs(b[y] - y2) + z);
    if (c == 1999999999) c = r;
    if (x1 == x2) c = r;
    cout << c << endl;
  }
}
