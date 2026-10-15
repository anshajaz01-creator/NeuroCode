#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
struct E {
  int to, next;
} mem[N << 1];
int n, x, y, num, h, t, c;
double ans;
int head[N], d1[N], d2[N], q[N];
bool vis[N];
void add(int x, int y) {
  num++;
  mem[num].to = y;
  mem[num].next = head[x];
  head[x] = num;
}
void init() {
  int k, u;
  for (int i = 1; i <= n; i++)
    if (d1[i] == 1) q[++t] = i;
  while (h < t) {
    k = q[++h];
    for (int j = head[k]; j; j = mem[j].next) {
      u = mem[j].to;
      d1[u]--;
      if (d1[u] == 1) q[++t] = u;
    }
  }
  c = n - t;
}
void dfs(int k) {
  int u;
  vis[k] = 1;
  for (int j = head[k]; j; j = mem[j].next) {
    u = mem[j].to;
    if (vis[u]) continue;
    d1[u] = d1[k] + 1;
    if (!d2[u]) {
      d2[u] = d2[k] + 1;
      ans += 1.0 / d2[u];
    } else
      ans += 1.0 / d1[u] - 2.0 / (d1[u] + d2[u] + c - 2);
    dfs(u);
  }
  vis[k] = 0;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &x, &y);
    x++;
    y++;
    add(x, y);
    add(y, x);
    d1[x]++;
    d1[y]++;
  }
  init();
  for (int i = 1; i <= n; i++) {
    memset(d1, 0, sizeof(d1));
    memset(d2, 0, sizeof(d2));
    memset(vis, 0, sizeof(vis));
    d1[i] = d2[i] = 1;
    dfs(i);
  }
  printf("%.6f\n", ans + n);
  return 0;
}
