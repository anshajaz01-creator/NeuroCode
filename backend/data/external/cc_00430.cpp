#include <bits/stdc++.h>
using namespace std;
const int N = 2 * 1e5 + 5;
map<int, int> ID;
int n, m, z, x[N], y, a, l, p[N], fp[N];
int erfen(int *x, int l, int r, int p) {
  int mid, ans;
  while (l <= r) {
    mid = (l + r) / 2;
    if (x[mid] <= p) {
      ans = mid;
      l = mid + 1;
    } else
      r = mid - 1;
  }
  return ans;
}
int work(int place, int R, int f, int yp) {
  int xx = place + f * R, y, np;
  if (f == 1)
    y = erfen(p, 1, n, xx), np = p[y];
  else
    y = erfen(fp, 1, n, -xx), np = -fp[y];
  if (np == place) return ID[np];
  if (yp == np) {
    R %= 2 * abs(np - place);
    if (R >= abs(np - place))
      return work(np, R - abs(np - place), -f, place);
    else
      return work(place, R, f, yp);
  } else
    return work(np, R - abs(np - place), -f, place);
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x[i]);
    p[i] = x[i];
    fp[i] = -x[i];
    ID[x[i]] = i;
  }
  sort(p + 1, p + n + 1);
  sort(fp + 1, fp + n + 1);
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d", &a, &l);
    z = 1;
    if (p[erfen(p, 1, n, x[a] + l)] != x[a])
      printf("%d\n", work(x[a], l, 1, 1e9 + 5));
    else
      printf("%d\n", work(x[a], l, -1, 1e9 + 5));
  }
}
