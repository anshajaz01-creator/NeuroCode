#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, ans, P[100001], sz[100001], vis[100001], pos[100001];
vector<int> v, G[100001], temp[100001];
int get(int x) { return x == P[x] ? x : P[x] = get(P[x]); }
void unite(int x, int y) {
  x = get(x);
  y = get(y);
  if (x == y) return;
  if (sz[x] < sz[y]) swap(x, y);
  sz[x] += sz[y];
  P[y] = x;
}
void dfs(int i) {
  vis[i] = 1;
  for (int j : G[i]) {
    if (!vis[j]) dfs(j);
  }
  v.push_back(i);
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) P[i] = i, sz[i] = 1;
  for (int i = 1; i <= m; ++i) {
    cin >> a >> b;
    unite(a, b);
    G[a].push_back(b);
  }
  for (int i = 1; i <= n; ++i) {
    temp[get(i)].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    if (temp[i].empty()) continue;
    v.clear();
    for (auto j : temp[i]) {
      if (!vis[j]) dfs(j);
    }
    bool ok = 1;
    for (int j = 0; j < v.size(); ++j) pos[v[j]] = j;
    for (auto j : v) {
      for (auto k : G[j]) {
        if (pos[k] > pos[j]) {
          ok = 0;
          break;
        }
      }
    }
    ans += temp[i].size() - ok;
  }
  cout << ans;
}
