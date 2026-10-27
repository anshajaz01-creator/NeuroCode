#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > g, r;
int n;
vector<int> color, st, scc;
int nSCC;
void dfs(int v, int flag) {
  color[v] = 1;
  for (int u : (flag ? g[v] : r[v]))
    if (!color[u]) dfs(u, flag);
  if (flag)
    st.push_back(v);
  else
    scc[v] = nSCC;
}
void traverse() {
  color = vector<int>(n, 0);
  st.clear();
  for (int i = 0; i < n; i++)
    if (!color[i]) dfs(i, 1);
  color = vector<int>(n, 0);
  scc = vector<int>(n);
  nSCC = 0;
  for (int i = n - 1; i >= 0; i--)
    if (!color[st[i]]) {
      dfs(st[i], 0);
      nSCC++;
    }
}
vector<int> hour, szSCC, valid;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int m, h, px, py, x, y;
  set<pair<int, int> > st;
  while (cin >> n >> m >> h) {
    hour = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> hour[i];
    st.clear();
    g = vector<vector<int> >(n);
    r = vector<vector<int> >(n);
    for (int i = 0; i < m; i++) {
      cin >> px >> py;
      px--;
      py--;
      x = min(px, py);
      y = max(px, py);
      if (st.count({x, y})) continue;
      st.insert({x, y});
      if ((hour[x] + 1) % h == hour[y]) {
        g[x].push_back(y);
        r[y].push_back(x);
      }
      if ((hour[y] + 1) % h == hour[x]) {
        g[y].push_back(x);
        r[x].push_back(y);
      }
    }
    traverse();
    szSCC = vector<int>(nSCC, 0);
    valid = vector<int>(nSCC, 1);
    for (int v = 0; v < n; v++) {
      szSCC[scc[v]]++;
      for (int u : g[v])
        if (scc[u] != scc[v]) valid[scc[v]] = 0;
    }
    int ans = n + 1, pos = -1;
    for (int i = 0; i < nSCC; i++)
      if (valid[i] && szSCC[i] < ans) {
        ans = szSCC[i];
        pos = i;
      }
    cout << ans << '\n';
    for (int i = 0; i < n; i++)
      if (scc[i] == pos) cout << i + 1 << " ";
    cout << '\n';
  }
  return 0;
}
