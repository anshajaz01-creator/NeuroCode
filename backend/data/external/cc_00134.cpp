#include <bits/stdc++.h>
using namespace std;
const int N = 990, INF = 0, MOD = 0;
int n, m, mark[N], up[N], h[N], ch[N];
vector<pair<int, int> > ans;
vector<int> adj[N], M[N], adj2[N], lv;
void DFS(int v, int p) {
  mark[v] = 1, up[v] = h[v], ch[v] = v;
  ;
  for (auto u : adj[v]) {
    if (u == p) continue;
    if (mark[u]) {
      up[v] = min(up[v], h[u]);
      continue;
    }
    h[u] = h[v] + 1;
    DFS(u, v);
    up[v] = min(up[v], up[u]);
    if (mark[u] != 2000) ch[v] = ch[u];
  }
  if (up[v] >= h[v]) mark[v] = 2000;
  if (v == 1) mark[v] = 2000;
  return;
}
void DFSD(int v, int p) {
  M[p].push_back(v);
  mark[v] = p;
  for (auto u : adj[v]) {
    if (mark[u] && mark[u] != 2000) continue;
    if (mark[u] == 2000)
      DFSD(u, u);
    else
      DFSD(u, p);
  }
  return;
}
void DFSB(int v, int p) {
  if (adj2[v].size() == 1) lv.push_back(v);
  for (auto u : adj2[v]) {
    if (u == p) continue;
    DFSB(u, v);
  }
  return;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  if (n == 2) return cout << -1, 0;
  for (int i = 0, u, v; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  DFS(1, 0);
  for (int i = 1; i <= n; i++)
    if (mark[i] == 1) mark[i] = 0;
  DFSD(1, 1);
  for (int i = 1; i <= n; i++) {
    for (auto u : adj[i]) {
      if (mark[u] == mark[i]) continue;
      adj2[mark[i]].push_back(mark[u]);
    }
  }
  DFSB(1, 0);
  int second = (int)lv.size();
  if ((int)second == 1) return cout << 0, 0;
  cout << (second + 1) / 2 << '\n';
  for (int i = 0; i < second; i++) {
    if (i + second / 2 >= second) break;
    cout << ch[lv[i]] << " " << ch[lv[i + second / 2]] << '\n';
  }
  return 0;
}
