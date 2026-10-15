#include <bits/stdc++.h>
using namespace std;
int n, tot, top, cnt;
int head[3100], nex[3100 << 1], to[3100 << 1];
int st[3100], deep[3100], cir[3100], inc[3100];
double ans;
vector<int> vec[3100];
void add(int x, int y) {
  tot++;
  nex[tot] = head[x];
  head[x] = tot;
  to[tot] = y;
}
void dfs(int x, int y) {
  st[++top] = x;
  for (int i = head[x]; i; i = nex[i])
    if (i != (y ^ 1)) {
      if (!deep[to[i]])
        deep[to[i]] = deep[x] + 1, dfs(to[i], i);
      else if (deep[to[i]] < deep[x]) {
        for (int j = top; st[j] != to[i]; j--)
          cir[++cnt] = st[j], inc[st[j]] = 1;
        cir[++cnt] = to[i];
        inc[to[i]] = 1;
      }
    }
  top--;
}
void cal(int x, int y, int tar) {
  deep[x] = deep[y] + 1;
  vec[tar].push_back(deep[x]);
  for (int i = head[x]; i; i = nex[i])
    if (to[i] != y && !inc[to[i]]) cal(to[i], x, tar);
}
double get(int v1, int v2, int v3) {
  return 1.0 / (v3 + v2) + 1.0 / (v3 + v1) - 1.0 / (v1 + v2 + v3);
}
void dfs1(int x, int y, int dep) {
  ans += 1.0 / dep;
  for (int i = head[x]; i; i = nex[i])
    if (to[i] != y) {
      if (inc[x] && inc[to[i]]) continue;
      dfs1(to[i], x, dep + 1);
    }
}
int main() {
  scanf("%d", &n);
  tot = 1;
  for (int i = 1, x, y; i <= n; i++) {
    scanf("%d%d", &x, &y);
    x++;
    y++;
    add(x, y);
    add(y, x);
  }
  deep[1] = 1;
  dfs(1, 0);
  for (int i = 1; i <= cnt; i++) cal(cir[i], 0, i);
  for (int i = 1; i <= cnt; i++)
    for (int j = i + 1; j <= cnt; j++) {
      int c1 = j - i - 1, c2 = cnt - c1 - 2;
      for (int k = 0; k < vec[i].size(); k++)
        for (int w = 0; w < vec[j].size(); w++)
          ans += get(c1, c2, vec[i][k] + vec[j][w]) * 2;
    }
  for (int i = 1; i <= n; i++) dfs1(i, 0, 1);
  printf("%.7lf\n", ans);
  return 0;
}
