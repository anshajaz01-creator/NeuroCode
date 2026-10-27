#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> G;
vector<int> color;
bool b;
void dfs(int s, int c) {
  color[s] = c;
  for (auto to : G[s]) {
    if (color[to] == -1) {
      dfs(to, (!c));
    } else {
      if (color[to] == color[s]) {
        b = 0;
      }
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int n, m, x, y;
  cin >> n >> m;
  G.resize(n + 1);
  color.resize(n + 1, -1);
  vector<pair<int, int>> pa;
  for (int i = 0; i < m; i++) {
    cin >> x >> y;
    G[x].push_back(y);
    G[y].push_back(x);
    pa.push_back({x, y});
  }
  b = 1;
  dfs(1, 0);
  if (!(b)) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    for (int i = 0; i < m; i++) {
      cout << (color[pa[i].first] < color[pa[i].second]);
    }
    cout << '\n';
  }
  return 0;
}
