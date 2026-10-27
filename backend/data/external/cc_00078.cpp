#include <bits/stdc++.h>
using namespace std;
const int Max = 1e5 + 10;
int fa[Max * 2];
int find(int x) { return fa[x] == -1 ? x : fa[x] = find(fa[x]); }
void Union(int x, int y) {
  int f1 = find(x), f2 = find(y);
  if (f1 != f2) fa[f1] = f2;
}
vector<int> ans1, ans2;
int vis[Max];
int main() {
  int n, m;
  while (~scanf("%d%d", &n, &m)) {
    memset(fa, -1, sizeof(fa));
    memset(vis, 0, sizeof(vis));
    int u, v, flag = 0;
    for (int i = 1; i <= m; i++) {
      scanf("%d%d", &u, &v);
      if (flag) continue;
      if (find(u) == find(v) || find(u + n) == find(v + n)) flag = 1;
      Union(u, v + n);
      Union(u + n, v);
      vis[u] = vis[v] = 1;
    }
    ans1.clear();
    ans2.clear();
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) continue;
      if (find(i) <= n)
        ans1.push_back(i);
      else
        ans2.push_back(i);
    }
    if (ans1.empty() || ans2.empty() || flag)
      puts("-1");
    else {
      if (ans1.size() > ans2.size()) swap(ans1, ans2);
      printf("%d\n", ans1.size());
      for (int i = 0; i < ans1.size(); i++) {
        if (i) printf(" ");
        printf("%d", ans1[i]);
      }
      printf("\n%d\n", ans2.size());
      for (int i = 0; i < ans2.size(); i++) {
        if (i) printf(" ");
        printf("%d", ans2[i]);
      }
      puts("");
    }
  }
  return 0;
}
