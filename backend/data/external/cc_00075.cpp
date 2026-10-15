#include <bits/stdc++.h>
using namespace std;
void cass() {
  ios::sync_with_stdio(0);
  cin.tie(0);
}
const int N = 2e5 + 2;
int n, m, pos[N];
vector<int> a[N];
void read() {
  cin >> n >> m;
  int u, v;
  for (int i = 1; i <= m; ++i) {
    cin >> u >> v;
    a[u].push_back(v);
    a[v].push_back(u);
  }
}
void DFS(int u) {
  for (int i = 0; i < a[u].size(); ++i) {
    if (pos[a[u][i]] != -1 && pos[u] == pos[a[u][i]]) {
      cout << -1;
      exit(0);
    } else if (pos[a[u][i]] == -1) {
      pos[a[u][i]] = 1 - pos[u];
      DFS(a[u][i]);
    }
  }
}
void solve() {
  memset(pos, -1, sizeof(pos));
  for (int i = 1; i <= n; ++i)
    if (pos[i] == -1 && a[i].size()) {
      pos[i] = 1;
      DFS(i);
    }
  int dem1 = 0, dem0 = 0;
  for (int i = 1; i <= n; ++i)
    if (pos[i] == 1)
      dem1++;
    else if (!pos[i])
      dem0++;
  cout << dem0 << '\n';
  for (int i = 1; i <= n; ++i)
    if (!pos[i]) cout << i << " ";
  cout << '\n' << dem1 << '\n';
  for (int i = 1; i <= n; ++i)
    if (pos[i] == 1) cout << i << " ";
}
int main() {
  cass();
  read();
  solve();
  return 0;
}
