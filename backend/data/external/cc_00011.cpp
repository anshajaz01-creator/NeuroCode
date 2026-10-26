#include <bits/stdc++.h>
using namespace std;
int n, m, flag, sum, tot, dis[3001][3001], e[100001], nt[100001], hd[100001],
    pa[100001], v[3001], d[3001], f[3001], sz[3001];
double ans;
void build(int x, int y) {
  tot++;
  e[tot] = y;
  nt[tot] = hd[x];
  hd[x] = tot;
}
void dfs(int x, int fa) {
  int i, y;
  if (v[x]) {
    y = fa;
    d[x] = 1;
    sum = 1;
    while (y != x) {
      sum++;
      d[y] = sum;
      y = pa[y];
    }
    flag = 1;
    return;
  }
  v[x] = 1;
  for (i = hd[x]; i; i = nt[i]) {
    if (e[i] == fa) continue;
    pa[e[i]] = x;
    dfs(e[i], x);
    if (flag) return;
  }
}
void get(int x, int len, int fa) {
  int i;
  if (d[x] && !flag) {
    flag = 1;
    sz[fa] = len;
    f[fa] = d[x];
  }
  v[x] = 1;
  dis[fa][x] = len;
  for (i = hd[x]; i; i = nt[i]) {
    if (v[e[i]]) continue;
    get(e[i], len + 1, fa);
  }
}
int main() {
  int i, j, x, y;
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%d%d", &x, &y);
    x++;
    y++;
    build(x, y);
    build(y, x);
  }
  dfs(1, 0);
  for (i = 1; i <= n; i++) {
    flag = 0;
    memset(v, 0, sizeof(v));
    get(i, 1, i);
  }
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (i == j)
        ans += 1;
      else if (f[i] == f[j])
        ans += 1 / (1.0 * abs(dis[i][j]));
      else {
        x = abs(f[i] - f[j]) - 1;
        y = sum - 2 - x;
        ans += 1.0 / (sz[i] + sz[j] + x) + 1.0 / (sz[i] + sz[j] + y) -
               1.0 / (sz[i] + sz[j] + x + y);
      }
    }
  }
  printf("%.10lf", ans);
}
