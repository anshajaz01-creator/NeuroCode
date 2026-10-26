#include <bits/stdc++.h>
using namespace std;
struct rec {
  int next, to;
} edge[100000 * 2 + 1];
int dfn[100000 + 1], low[100000 + 1], head[100000 + 1], a[100000 + 1],
    b[100000 + 1], s[100000 + 1], n, m, h, cnt = 1, ans = 2147483647, tot = 0;
bool bz[100000 + 1], bz1[100000 + 1];
void add(int u, int v) {
  edge[cnt].to = v, edge[cnt].next = head[u];
  head[u] = cnt++;
}
void tarjan(int k) {
  dfn[k] = low[k] = ++tot, s[++s[0]] = k, bz1[k] = true, bz[k] = false;
  for (int i = head[k]; i; i = edge[i].next) {
    if (!dfn[edge[i].to]) {
      tarjan(edge[i].to);
      low[k] = min(low[k], low[edge[i].to]);
    } else if (bz1[edge[i].to])
      low[k] = min(low[k], dfn[edge[i].to]);
  }
  if (dfn[k] == low[k]) {
    bool bz2 = true;
    int size = 0;
    for (int i = s[0]; i; i = (s[i] == k ? 0 : i - 1)) {
      ++size;
      for (int j = head[s[i]]; j; j = edge[j].next)
        if (!bz1[edge[j].to]) bz2 = false;
    }
    if (bz2 && size < ans) {
      ans = size;
      for (int i = s[0]; i; i = (s[i] == k ? 0 : i - 1), size--, --s[0]) {
        bz1[s[i]] = false, b[ans - size + 1] = s[i];
      }
    } else {
      for (int i = s[0]; i; i = (s[i] == k ? 0 : i - 1), --s[0])
        bz1[s[i]] = false;
    }
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &h);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  int x, y;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &x, &y);
    if ((a[x] + 1) % h == a[y]) add(x, y);
    if ((a[y] + 1) % h == a[x]) add(y, x);
  }
  memset(bz, true, sizeof bz);
  memset(dfn, 0, sizeof dfn);
  memset(low, 0, sizeof low);
  s[0] = 0;
  for (int i = 1; i <= n; i++) {
    if (bz[i]) tarjan(i);
    tot = 0;
  }
  printf("%d\n", ans);
  for (int i = 1; i <= ans; i++) printf("%d ", b[i]);
  return 0;
}
