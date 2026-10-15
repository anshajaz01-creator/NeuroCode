#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 1;
vector<int> g[maxn];
int n, m, k, num[maxn], pre[maxn], maxx = 0, flag = 0;
void dfs(int u, int fa, int deep) {
  num[u] = deep;
  pre[u] = fa;
  for (int to : g[u]) {
    if (flag) return;
    if (to == fa) continue;
    if (num[to] > 0) {
      if (num[u] - num[to] + 1 >= k + 1) {
        printf("%d\n", num[u] - num[to] + 1);
        while (u != to) {
          printf("%d ", u);
          u = pre[u];
        }
        printf("%d", to);
        flag = 1;
        return;
      }
      continue;
    }
    dfs(to, u, deep + 1);
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 0, 1);
}
