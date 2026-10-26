#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
namespace SCC {
const int N = 101010;
int dfn[N], low[N], st[N], top, id[N], col, cnt, big[N];
void dfs(int u, vector<int> g[]) {
  dfn[u] = low[u] = ++cnt;
  st[top++] = u;
  for (auto v : g[u]) {
    if (!dfn[v]) {
      dfs(v, g);
      low[u] = min(low[u], low[v]);
    } else if (!id[v])
      low[u] = min(low[u], dfn[v]);
  }
  if (low[u] == dfn[u]) {
    ++col;
    do {
      id[st[--top]] = col;
      big[col]++;
    } while (st[top] != u);
  }
}
int out[N];
int solve(int n, vector<int> g[]) {
  fill_n(big, n + 1, 0);
  fill_n(dfn, n + 1, top = 0);
  fill_n(low, n + 1, col = 0);
  fill_n(id, n + 1, cnt = 0);
  for (int i = (1); i < (n + 1); i++)
    if (!dfn[i]) dfs(i, g);
  fill_n(out, col + 1, 0);
  for (int i = (1); i < (n + 1); i++)
    for (int v = 0; v < (int)g[i].size(); ++v) {
      int j = g[i][v];
      if (id[i] != id[j]) out[id[i]]++;
    }
  return col;
}
vector<int> gao(int n) {
  int mn = 1e9, ans;
  for (int i = (1); i < (col + 1); i++) {
    if (out[i] == 0 && big[i] < mn) ans = i, mn = min(mn, big[i]);
  }
  vector<int> t;
  for (int i = (1); i < (n + 1); i++)
    if (id[i] == ans) t.push_back(i);
  return t;
}
}  // namespace SCC
int a[N];
vector<int> g[N];
int main() {
  int n, m, h;
  cin >> n >> m >> h;
  int u, v;
  for (int i = (1); i < (n + 1); i++) cin >> a[i];
  for (int i = (1); i < (m + 1); i++) {
    cin >> u >> v;
    if ((a[u] + 1) % h == a[v]) g[u].push_back(v);
    if ((a[v] + 1) % h == a[u]) g[v].push_back(u);
  }
  SCC::solve(n, g);
  vector<int> ans = SCC::gao(n);
  cout << (int)ans.size() << "\n";
  for (auto v : ans) cout << v << " ";
  return 0;
}
