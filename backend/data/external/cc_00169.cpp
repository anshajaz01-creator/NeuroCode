#include <bits/stdc++.h>
using namespace std;
int n, m, k;
vector<string> g;
vector<int> w;
int dfs(int node) {
  if (g[node / m][node % m] == '#') return 0;
  w[node] = 1;
  if (node / m && !w[node - m]) w[node] += dfs(node - m);
  if (node / m < n - 1 && !w[node + m]) w[node] += dfs(node + m);
  if (node % m && !w[node - 1]) w[node] += dfs(node - 1);
  if (node % m < m - 1 && !w[node + 1]) w[node] += dfs(node + 1);
  return w[node];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> k;
  g = vector<string>(n);
  for (int i = 0; i < n; i++) cin >> g[i];
  w = vector<int>(n * m);
  int r;
  for (int i = 0; i < n * m; i++)
    if (g[i / m][i % m] == '.') {
      dfs(i);
      r = i;
      break;
    }
  set<pair<int, int>> s;
  for (int i = 0; i < n * m; i++)
    if (w[i]) s.insert({w[i], i});
  auto it = s.begin();
  for (int i = 0; i < k; it++, i++) g[it->second / m][it->second % m] = 'X';
  for (auto r : g) cout << r << "\n";
  return 0;
}
