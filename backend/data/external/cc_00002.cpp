#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<pair<int, int>>> g(n);
  vector<int> from(m), to(m);
  for (int i = 0; i < m; i++) {
    cin >> from[i] >> to[i];
    from[i]--;
    to[i]--;
    g[from[i]].emplace_back(to[i], i);
    g[to[i]].emplace_back(from[i], i);
  }
  vector<int> res(m), alive(m, 1), que, deg(n);
  for (int i = 0; i < n; i++) {
    deg[i] = (int)g[i].size();
    if (deg[i] < k) que.push_back(i);
  }
  int ind = 0;
  for (int i = m - 1; i >= 0; i--) {
    while (ind < (int)que.size()) {
      int u = que[ind];
      for (auto p : g[u]) {
        if (!alive[p.second]) continue;
        alive[p.second] = 0;
        deg[u]--;
        if (deg[p.first] == k) que.push_back(p.first);
        deg[p.first]--;
      }
      ind++;
    }
    res[i] = n - que.size();
    if (alive[i]) {
      alive[i] = 0;
      if (deg[from[i]] == k) que.push_back(from[i]);
      if (deg[to[i]] == k) que.push_back(to[i]);
      deg[from[i]]--;
      deg[to[i]]--;
    }
  }
  for (int i : res) cout << i << '\n';
}
