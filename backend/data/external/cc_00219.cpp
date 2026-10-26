#include <bits/stdc++.h>
using namespace std;
const int MAX = (int)1e5;
vector<int> adj[MAX + 5];
int q[MAX + 5], p[MAX + 5];
bool fr[MAX + 5];
int n, m, k, cnt;
bool c;
void dfs(int u) {
  if (!c) return;
  cnt++;
  q[cnt] = u;
  p[u] = cnt;
  fr[u] = false;
  bool ok = false;
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (fr[v]) dfs(v), ok = true;
  }
  if (!ok) {
    c = false;
    return;
  }
}
int main() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  memset(fr, true, sizeof(fr));
  cnt = 0;
  c = true;
  dfs(1);
  int u = q[cnt];
  int t = n + 1;
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (p[v] < t) t = p[v];
  }
  printf("%d\n", cnt - t + 1);
  for (int i = t; i <= cnt; i++) {
    printf("%d ", q[i]);
  }
}
