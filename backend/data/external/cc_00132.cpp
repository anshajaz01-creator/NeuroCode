#include <bits/stdc++.h>
using namespace std;
int n, m;
map<pair<int, int>, int> mp;
int low[910], dfn[910], tim, stk[910], top, bel[910], deg[910], ver[910];
bool vis[910];
int bcccnt = 0;
vector<int> v[910];
vector<int> bcc[910];
void output(int a, int b) {
  for (auto &x : bcc[a]) {
    for (auto &y : bcc[b]) {
      if (mp.find(make_pair(x, y)) == mp.end()) {
        printf("%d %d\n", x, y);
        return;
      }
    }
  }
}
void dfs(int np, int fath) {
  low[np] = dfn[np] = ++tim;
  vis[np] = 1;
  stk[++top] = np;
  for (auto &x : v[np]) {
    if (x == fath) continue;
    if (!dfn[x]) {
      dfs(x, np);
      low[np] = min(low[np], low[x]);
    } else
      low[np] = min(low[np], dfn[x]);
  }
  if (low[np] == dfn[np]) {
    bcccnt++;
    ver[bcccnt] = np;
    int tmp;
    while ((tmp = stk[top--])) {
      bel[tmp] = bcccnt;
      bcc[bcccnt].push_back(tmp);
      if (tmp == np) break;
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  if (n == 2) {
    puts("-1");
    return 0;
  }
  for (int i = 1, ti, tj; i <= m; i++) {
    scanf("%d%d", &ti, &tj);
    v[ti].push_back(tj);
    v[tj].push_back(ti);
  }
  dfs(1, 0);
  if (bcccnt == 1) {
    puts("0");
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    for (auto &x : v[i]) {
      if (bel[x] == bel[i]) continue;
      if (mp.find(make_pair(x, i)) != mp.end()) continue;
      deg[bel[x]]++;
      deg[bel[i]]++;
      mp[make_pair(x, i)] = mp[make_pair(i, x)] = 1;
    }
  }
  vector<int> ans;
  for (int i = 1; i <= bcccnt; i++)
    if (deg[i] == 1) ans.push_back(i);
  printf("%d\n", (ans.size() + 1) >> 1);
  for (int i = 0; i < ((ans.size() + 1) >> 1); i++)
    output(ans[i], ans[min(ans.size() - 1, i + ans.size() / 2)]);
  return 0;
}
