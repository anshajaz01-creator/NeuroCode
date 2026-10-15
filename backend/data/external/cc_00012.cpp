#include <bits/stdc++.h>
using namespace std;
inline int read() {
  bool f = true;
  register int x = 0;
  char ch;
  while (!isdigit(ch = getchar()))
    if (ch == '-') f = false;
  while (isdigit(ch)) {
    x = (x << 1) + (x << 3) + ch - '0';
    ch = getchar();
  }
  return f ? x : -x;
}
double ans;
int n, cnt, C, H, T;
int q[3005], d[3005], d2[3005];
bool vis[3005];
vector<int> e[3005];
void dfs(int x) {
  vis[x] = 1;
  for (int i = 0; i < e[x].size(); i++) {
    int b = e[x][i];
    if (!vis[b]) {
      d2[b] = d2[x] + 1;
      if (!d[b]) {
        d[b] = d[x] + 1;
        ans += 1.0 / d[b];
      } else
        ans = ans + 1.0 / d2[b] - 2.0 / (d[b] + d2[b] + C - 2);
      dfs(b);
    }
  }
  vis[x] = 0;
}
int main() {
  n = read();
  for (int i = 1, u, v; i <= n; i++) {
    u = read() + 1;
    v = read() + 1;
    e[u].push_back(v);
    e[v].push_back(u);
    d[u]++;
    d[v]++;
  }
  for (int i = 1; i <= n; i++)
    if (d[i] == 1) q[T++] = i;
  while (H != T) {
    int now = q[H];
    H++;
    for (int i = 0; i < e[now].size(); i++) {
      int b = e[now][i];
      d[b]--;
      if (d[b] == 1) {
        q[T++] = b;
      }
    }
  }
  C = n - T;
  for (int i = 1; i <= n; i++) {
    memset(d, 0, sizeof(d));
    memset(d2, 0, sizeof(d2));
    d[i] = d2[i] = 1;
    dfs(i);
  }
  printf("%.10lf\n", ans + n);
  return 0;
}
