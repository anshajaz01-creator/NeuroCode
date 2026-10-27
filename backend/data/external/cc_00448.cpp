#include <bits/stdc++.h>
using namespace std;
const int maxn = 200005;
const int INF = 0x3f3f3f3f;
int cost[maxn];
int nextt[maxn];
int dfn[maxn];
int n;
int ans;
int dfs_clock;
stack<int> s;
int dfs(int pos) {
  dfn[pos] = dfs_clock++;
  int tmp;
  if (dfn[nextt[pos]] == 0)
    tmp = dfs(nextt[pos]);
  else
    tmp = dfn[nextt[pos]];
  if (tmp < dfn[pos]) s.push(pos);
  if (tmp == dfn[pos]) {
    s.push(pos);
    int minn = INF;
    while (!s.empty()) {
      minn = min(minn, cost[s.top()]);
      s.pop();
    }
    ans += minn;
  }
  return min(dfn[pos], tmp);
}
int main() {
  ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &cost[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &nextt[i]);
  memset(dfn, 0, sizeof(dfn));
  dfs_clock = 1;
  for (int i = 1; i <= n; i++) {
    while (!s.empty()) s.pop();
    if (dfn[i] == 0) {
      dfs(i);
    }
  }
  printf("%d\n", ans);
  return 0;
}
