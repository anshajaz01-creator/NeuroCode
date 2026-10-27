#include <bits/stdc++.h>
using namespace std;
int n, m, u, v;
vector<int> g[100005], gr[100005];
vector<int> order;
bool used[100005];
int G[100005], C[100005], k = 0;
void dfs1(int x) {
  used[x] = 1;
  for (int(i) = (0); (i) < (g[x].size()); (i)++) {
    int nn = g[x][i];
    if (!used[nn]) dfs1(nn);
  }
  order.push_back(x);
}
int dfs2(int x) {
  used[x] = 1;
  G[x] = k;
  int ans = 1, nn;
  for (int(i) = (0); (i) < (gr[x].size()); (i)++) {
    nn = gr[x][i];
    if (!used[nn]) ans += dfs2(nn);
  }
  return ans;
}
int dfs3(int x) {
  used[x] = 1;
  int ans = (C[G[x]] == 1), nn;
  for (int(i) = (0); (i) < (g[x].size()); (i)++) {
    nn = g[x][i];
    if (!used[nn]) ans &= dfs3(nn);
  }
  for (int(i) = (0); (i) < (gr[x].size()); (i)++) {
    nn = gr[x][i];
    if (!used[nn]) ans &= dfs3(nn);
  }
  return ans;
}
int main() {
  scanf("%d%d", &(n), &(m));
  for (int(i) = (0); (i) < (m); (i)++) {
    scanf("%d%d", &(u), &(v));
    g[u].push_back(v);
    gr[v].push_back(u);
  }
  for (int i = 1; i <= n; i++)
    if (!used[i]) dfs1(i);
  reverse(order.begin(), order.end());
  memset((used), (0), sizeof(used));
  for (int(i) = (0); (i) < (n); (i)++)
    if (!used[order[i]]) {
      C[k] = dfs2(order[i]);
      k++;
    }
  memset((used), (0), sizeof(used));
  int ans = n;
  for (int i = 0; i < n; i++)
    if (!used[order[i]]) ans -= dfs3(order[i]);
  printf("%d\n", ans);
}
