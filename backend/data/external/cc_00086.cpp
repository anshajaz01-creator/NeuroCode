#include <bits/stdc++.h>
const int N = 200005;
using std::vector;
vector<vector<int>> dis[N];
vector<int> dis2[N], e[N];
int deep[N], in[N], out[N], siz[N], c[N], d[N], a[N], idn, cnt, n, x, id[N], Q;
long long m;
std::queue<int> q;
void dfs(int col, int x, int dep, int cn) {
  in[x] = ++idn;
  deep[x] = dep;
  dis2[dep].push_back(idn);
  dis[col][(dep + cn) % siz[col]].push_back(dep);
  for (auto u : e[x]) dfs(col, u, dep + 1, cn);
  out[x] = idn;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    d[a[i]]++;
  }
  for (int i = 1; i <= n; i++)
    if (!d[i]) q.push(i);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    e[a[x]].push_back(x);
    if (!(--d[a[x]])) q.push(a[x]);
  }
  for (int i = 1; i <= n; i++)
    if (d[i]) {
      if (!c[i]) {
        c[i] = ++cnt;
        siz[cnt] = 1;
        for (int x = a[i]; x != i; x = a[x]) ++siz[cnt], c[x] = cnt;
        int tt = siz[cnt];
        for (int x = a[i]; x != i; x = a[x]) id[x] = --tt;
        dis[cnt].resize(siz[cnt] + 1);
      }
      dfs(c[i], i, 0, id[i]);
    }
  scanf("%d", &Q);
  for (int i = 1; i <= cnt; i++)
    for (int j = 0; j < siz[i]; j++)
      std::sort(dis[i][j].begin(), dis[i][j].end());
  while (Q--) {
    scanf("%lld%d", &m, &x);
    if (d[x]) {
      int col = c[x], t = (id[x] + m) % siz[col];
      m = (int)std::min(m, (long long)n);
      int p = std::upper_bound(dis[col][t].begin(), dis[col][t].end(), m) -
              dis[col][t].begin();
      printf("%d\n", p);
    } else {
      if (deep[x] + m > n) {
        puts("0");
        continue;
      }
      int t = deep[x] + m;
      int pl = std::lower_bound(dis2[t].begin(), dis2[t].end(), in[x]) -
               dis2[t].begin();
      int pr = std::upper_bound(dis2[t].begin(), dis2[t].end(), out[x]) -
               dis2[t].begin();
      printf("%d\n", pr - pl);
    }
  }
}
