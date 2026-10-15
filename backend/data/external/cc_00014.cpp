#include <bits/stdc++.h>
using namespace std;
const int INF = 1 << 29, N = 5e5 + 50, M = 1e6 + 5;
inline int read() {
  int f = 1, x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
void judge() {
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
}
int n, head[N], nxt[N], toit[N], s[N], top, cycle, cnt, bel[N], dis[N];
bool vis[N], flag, incir[N];
void adde(int a, int b) { toit[++cnt] = b, nxt[cnt] = head[a], head[a] = cnt; }
void getcir(int v, int fa) {
  s[++top] = v;
  vis[v] = 1;
  for (int(k) = head[v]; k; k = nxt[k])
    if (toit[k] != fa) {
      if (flag) return;
      if (vis[toit[k]]) {
        while (s[top] != toit[k]) incir[s[top--]] = 1, cycle++;
        cycle++;
        incir[s[top]] = 1;
        flag = 1;
        return;
      }
      getcir(toit[k], v);
    }
  top--;
}
void dfs1(int v, int fa, int rt, int d) {
  bel[v] = rt;
  dis[v] = d;
  for (int(k) = head[v]; k; k = nxt[k])
    if (toit[k] != fa && !incir[toit[k]]) dfs1(toit[k], v, rt, d + 1);
}
int now, first;
double ans;
void dfs2(int v, int fa, int d) {
  if (v == bel[now]) {
    if (first) return;
    first++;
  }
  ans += 1. / (d + 1);
  for (int(k) = head[v]; k; k = nxt[k])
    if (toit[k] != fa) dfs2(toit[k], v, d + 1);
}
int main() {
  n = read();
  for (int(i) = (1); (i) <= (n); (i)++) {
    int a = read(), b = read();
    a++;
    b++;
    adde(a, b);
    adde(b, a);
  }
  getcir(1, 0);
  for (int(i) = (1); (i) <= (n); (i)++)
    if (incir[i]) dfs1(i, 0, i, 0);
  for (int(i) = (1); (i) <= (n); (i)++) now = i, first = 0, dfs2(i, 0, 0);
  for (int(i) = (1); (i) <= (n); (i)++)
    for (int(j) = (1); (j) <= (n); (j)++)
      if (bel[i] != bel[j]) ans -= 1. / (dis[i] + dis[j] + cycle);
  printf("%lf", ans);
}
