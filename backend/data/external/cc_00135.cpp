#include <bits/stdc++.h>
using namespace std;
const int N = 200004;
vector<int> g[N], h[N];
int a[N], z[N], n, m;
int dfn[N], low[N], col[N], idx = 0, c = 0;
int st[N], pt = 0;
bool ins[N];
void tarjan(int u, int fa) {
  dfn[u] = low[u] = ++idx;
  st[++pt] = u;
  ins[u] = 1;
  for (int v : g[u]) {
    if (v == fa) continue;
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if (ins[v])
      low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    ++c;
    int v;
    do {
      v = st[pt--];
      col[v] = c;
      ins[v] = 0;
    } while (v != u);
  }
}
int f[N], lv[N], w = 0;
int main() {
  int k, x, y;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  tarjan(1, 0);
  if (n == 2) return puts("-1"), 0;
  if (c == 1) return puts("0"), 0;
  for (int u = 1; u <= n; u++)
    for (int v : g[u])
      if (col[u] != col[v]) h[col[u]].push_back(col[v]);
  vector<int> lv;
  for (int i = 1; i <= c; i++)
    if (h[i].size() == 1) lv.push_back(i);
  for (int i = 1; i <= n; i++) f[col[i]] = i;
  if (c == 2) {
    auto it = find(g[f[1]].begin(), g[f[1]].end(), f[2]);
    if (it != g[f[1]].end()) {
      for (int i = n; i >= 1; i--) f[col[i]] = i;
    }
    return printf("1\n%d %d\n", f[1], f[2]), 0;
  }
  printf("%d\n", (lv.size() + 1) / 2);
  vector<pair<int, int> > v;
  int sz = lv.size();
  sz >>= 1;
  for (int i = sz; i < lv.size(); i++)
    v.push_back(pair<int, int>(f[lv[i - sz]], f[lv[i]]));
  for (pair<int, int> &pa : v) printf("%d %d\n", pa.first, pa.second);
}
