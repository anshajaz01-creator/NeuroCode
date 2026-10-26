#include <bits/stdc++.h>
using namespace std;
int n, m, x, len, dir, t, y;
bool fin;
pair<int, int> a[(200100)];
int loc[(200100)];
int binary_right(int x, int t) {
  int l = x, r = n, mid;
  while (l < r) {
    mid = (l + r + 1) / 2;
    if (a[mid].first <= t)
      l = mid;
    else
      r = mid - 1;
  }
  return l;
}
int binary_left(int x, int t) {
  int l = 1, r = x, mid;
  while (l < r) {
    mid = (l + r) / 2;
    if (a[mid].first >= t)
      r = mid;
    else
      l = mid + 1;
  }
  return l;
}
void In() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i].first);
    a[i].second = i;
  }
  sort(a + 1, a + n + 1);
}
void solve() {
  for (int i = 1; i <= n; ++i) loc[a[i].second] = i;
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &len);
    x = loc[x];
    dir = 1;
    fin = 0;
    while (!fin) {
      t = a[x].first + dir * len;
      if (dir == 1) {
        y = binary_right(x, t);
        if (binary_left(y, a[y].first - (len - a[y].first + a[x].first)) == x) {
          if (y == x)
            fin = 1;
          else
            len %= 2 * (a[y].first - a[x].first);
        } else {
          dir = -1;
          len -= (a[y].first - a[x].first);
          x = y;
        }
      } else {
        y = binary_left(x, t);
        if (binary_right(y, a[y].first + (len - a[x].first + a[y].first)) ==
            x) {
          if (y == x)
            fin = 1;
          else
            len %= 2 * (a[x].first - a[y].first);
        } else {
          dir = 1;
          len -= (a[x].first - a[y].first);
          x = y;
        }
      }
    }
    printf("%d\n", a[x].second);
  }
}
int main() {
  In();
  solve();
}
