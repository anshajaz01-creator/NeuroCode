#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
const int inf = 0x3f3f3f3f;
int n, m;
int first[maxn], sign;
int vis[maxn];
int a[maxn][2];
struct node {
  int to, w, next;
} edge[maxn << 1];
void init() {
  for (int i = 0; i <= n; i++) first[i] = -1;
  sign = 0;
}
void add_edge(int u, int v, int w) {
  edge[sign].to = v;
  edge[sign].w = w;
  edge[sign].next = first[u];
  first[u] = sign++;
}
bool flag1 = 0;
void dfs(int x, int flag) {
  vis[x] = flag;
  for (int i = first[x]; ~i; i = edge[i].next) {
    int to = edge[i].to;
    if (vis[to] == vis[x]) {
      flag1 = 1;
      return;
    }
    if (vis[to] == -1) {
      dfs(to, flag ^ 1);
    }
  }
  return;
}
int main() {
  scanf("%d%d", &n, &m);
  init();
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    add_edge(u, v, 1);
    add_edge(v, u, 1);
    a[i][0] = u;
    a[i][1] = v;
  }
  memset(vis, -1, sizeof(vis));
  dfs(1, 1);
  if (flag1)
    puts("NO");
  else {
    puts("YES");
    for (int i = 1; i <= m; i++) {
      if (vis[a[i][0]] == 1)
        printf("0");
      else
        printf("1");
    }
  }
  return 0;
}
