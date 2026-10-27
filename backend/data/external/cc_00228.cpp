#include <bits/stdc++.h>
using namespace std;
vector<int> visited;
bool flag = true;
struct item {
  int v;
  int u;
};
void dfs(vector<vector<int>> &g, int v, int r) {
  visited[v] = r;
  for (int next : g[v]) {
    if (visited[next] != -1 && visited[next] == visited[v]) flag = false;
    if (visited[next] == -1) {
      dfs(g, next, (r + 1) % 2);
    }
  }
}
int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<vector<int>> g(n + 1);
  vector<item> e;
  for (int i = 1; i <= m; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    g[a].push_back(b);
    g[b].push_back(a);
    e.push_back(item{a, b});
  }
  visited.resize(n + 1, -1);
  dfs(g, 1, 0);
  if (!flag) {
    printf("NO\n");
    return 0;
  }
  printf("YES\n");
  for (int i = 0; i < (int)e.size(); i++) {
    if (visited[e[i].v] > visited[e[i].u])
      printf("1");
    else
      printf("0");
  }
  return 0;
}
