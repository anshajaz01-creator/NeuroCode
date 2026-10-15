#include <bits/stdc++.h>
using namespace std;
const int G = 1000 * 100 + 10;
vector<int> e[G], bnam[G], ans;
int h[G], up[G], st[G], mj[G], to[G], x, y;
void dfs(int v) {
  up[v] = h[v];
  st[y++] = v;
  for (int i = 0; i < e[v].size(); i++) {
    int u = e[v][i];
    if (!h[u]) {
      h[u] = h[v] + 1;
      dfs(u);
      up[v] = min(up[v], up[u]);
    } else if (h[u] != (h[v] - 1)) {
      up[v] = min(up[v], h[u]);
    }
  }
  if (h[v] == up[v]) {
    to[x] = st[y - 1];
    do {
      mj[st[--y]] = x;
    } while (st[y] != v);
    x++;
  }
}
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    e[a].push_back(b);
    e[b].push_back(a);
  }
  h[0] = 1;
  dfs(0);
  if (n <= 2) {
    cout << -1;
    return 0;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < e[i].size(); j++) {
      int u = e[i][j];
      if (mj[i] != mj[u]) bnam[mj[i]].push_back(mj[u]);
    }
  }
  int leaf = 0;
  for (int i = 0; i < x; i++) {
    if (bnam[i].size() == 1) {
      leaf++;
      ans.push_back(to[i] + 1);
    }
  }
  int anss = (leaf + 1) / 2;
  cout << anss << '\n';
  if (leaf % 2) anss--;
  for (int i = anss; i < leaf; ++i)
    cout << ans[i] << " " << ans[i - anss] << '\n';
  return 0;
}
