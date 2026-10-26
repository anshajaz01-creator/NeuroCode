#include <bits/stdc++.h>
using namespace std;
map<int, int> ch;
int c, n, m, a[100010], b[2010], ds[100010], d[100010], check[100010], pos,
    check2[100010];
int main() {
  int i, j, sw, cc = 0;
  scanf("%d %d", &n, &m);
  for (i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (i = 1; i <= m; i++) {
    scanf("%d", &b[i]);
    ch[b[i]] = 1;
  }
  sort(a + 1, a + n + 1);
  for (i = 1; i < n; i++) {
    check2[i] = cc;
    if (a[i + 1] != a[i] + 1) {
      pos = i;
      check[i] = pos;
      cc++;
    } else
      check[i] = pos;
  }
  check2[n] = cc;
  sort(b + 1, b + m + 1);
  for (i = 1; i <= n; i++) {
    if (ch[a[i]])
      sw = 1;
    else
      sw = 0;
    ds[i] = max(ds[i], d[check[i - 1]] + sw);
    c = 0;
    for (j = m; j >= 1; j--) {
      if (b[j] >= a[i]) continue;
      c++;
      if (i - (a[i] - b[j]) - 1 >= 0)
        ds[i] = max(ds[i], d[check[i - (a[i] - b[j]) - 1]] + c + sw);
    }
    c = 0;
    for (j = 1; j <= m; j++) {
      if (a[i] < b[j]) {
        c++;
        if (i + b[j] - a[i] <= n)
          d[i + b[j] - a[i]] = max(d[i + b[j] - a[i]], ds[i] + c);
        if (i + b[j] - a[i] <= n && check2[i + b[j] - a[i]] == check2[i])
          ds[i + b[j] - a[i]] = max(ds[i + b[j] - a[i]], ds[i] + c);
      }
    }
    d[i] = max(ds[i], d[i]);
    d[i] = max(d[i], d[i - 1]);
  }
  printf("%d", d[n]);
  return 0;
}
