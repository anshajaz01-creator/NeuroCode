#include <bits/stdc++.h>
using namespace std;
struct o {
  long long x, y, z, t;
};
long long n, m, a[1000000] = {0}, b[10000000] = {0};
o c[1000000] = {0};
bool used[10000000] = {0};
int main() {
  cin >> n >> m;
  for (int k = 1; k <= n; ++k) a[k] = 1000000000;
  for (int k1 = 1; k1 <= m; ++k1) {
    long long t, l, r, a1;
    cin >> t >> l >> r >> a1;
    c[k1].x = t;
    c[k1].y = l;
    c[k1].z = r;
    c[k1].t = a1;
    if (t == 2) {
      long long y = 1000000000;
      for (int k = l; k <= r; ++k) {
        if (!used[k]) {
          a[k] = min(a1 - b[k], a[k]);
          used[k] = 0;
        }
      }
    } else
      for (int k = l; k <= r; ++k) {
        b[k] = b[k] + a1;
        used[k] = 0;
      }
  }
  bool j = 1;
  for (int k = 1; k <= n; ++k) b[k] = a[k];
  for (int k = 1; k <= m; ++k) {
    if (c[k].x == 2) {
      long long maxc = -1000000000;
      for (int i = c[k].y; i <= c[k].z; ++i) maxc = max(maxc, b[i]);
      if (maxc != c[k].t) {
        j = 0;
        break;
      }
    } else
      for (int i = c[k].y; i <= c[k].z; ++i) b[i] += c[k].t;
  }
  if (j) {
    cout << "YES" << endl;
    for (int k = 1; k <= n; ++k) {
      cout << a[k];
      if (k < n) cout << ' ';
    }
    return 0;
  } else
    cout << "NO";
  return 0;
}
