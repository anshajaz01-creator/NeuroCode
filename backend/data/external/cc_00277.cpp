#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 1;
struct DSU {
  int p[maxn];
  int cnt[maxn];
  inline bool is_root(int x) { return x == p[x]; }
  int pa(int x) { return is_root(x) ? x : p[x] = pa(p[x]); }
  void merge(int x, int y) {
    x = pa(x), y = pa(y);
    if (x != y) {
      p[x] = y;
      cnt[y] += cnt[x];
    }
  }
  void init(int n) {
    for (int i = 1; i <= n; ++i) cnt[i] = 1, p[i] = i;
  }
} one, two;
vector<int> g[maxn];
int in[maxn];
bool mark[maxn];
int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  one.init(n);
  memset(in + 1, 0, n * sizeof(in[0]));
  memset(mark + 1, 0, n * sizeof(mark[0]));
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    ++in[v];
    one.merge(u, v);
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    if (one.is_root(i)) ans += one.cnt[i] - 1;
  queue<int> q;
  for (int i = 1; i <= n; ++i)
    if (in[i] == 0) q.push(i);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (auto nxt : g[cur])
      if (--in[nxt] == 0) q.push(nxt);
  }
  for (int i = 1; i <= n; ++i)
    if (in[i] != 0 && mark[one.pa(i)] == false) {
      mark[one.pa(i)] = true;
      ++ans;
    }
  printf("%d\n", ans);
}
