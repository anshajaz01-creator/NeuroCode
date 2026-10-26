#include <bits/stdc++.h>
using namespace std;
int n, m, u, v, flag, num, vis[100100];
vector<int> edge[100100];
queue<int> sk[100100];
struct G {
  int a, b, c;
} ans[100100];
void dfs(int u, int father) {
  vis[u] = true;
  for (int i = 0; i < edge[u].size(); ++i) {
    int v = edge[u][i];
    if (vis[v] == false)
      dfs(v, u);
    else if (v != father && vis[v] == true)
      sk[v].push(u);
  }
  while (sk[u].size() >= 2) {
    int x = sk[u].front();
    sk[u].pop();
    int y = sk[u].front();
    sk[u].pop();
    ans[++num] = {x, u, y};
  }
  if (sk[u].size() == 1) {
    if (father == 0) flag = 1;
    int x = sk[u].front();
    sk[u].pop();
    ans[++num] = {x, u, father};
  } else
    sk[father].push(u);
}
int main() {
  cin >> n >> m;
  if (m % 2 == 1) {
    cout << "No solution" << endl;
    return 0;
  }
  for (int i = 1; i <= m; ++i) {
    cin >> u >> v;
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  if (flag == 1)
    cout << "No solution" << endl;
  else {
    for (int i = 1; i <= num; ++i) {
      cout << ans[i].a << " " << ans[i].b << " " << ans[i].c << endl;
    }
  }
  return 0;
}
