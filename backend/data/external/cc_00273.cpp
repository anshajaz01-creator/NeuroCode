#include <bits/stdc++.h>
using namespace std;
const long long maxn = 2e5 + 100;
const long long mod = 1e9 + 7;
const long long base = 2e9 + 1;
long long col[maxn];
long long siz[maxn];
vector<long long> adj[maxn];
long long par[maxn];
long long find_par(long long u) {
  if (u == par[u]) return u;
  return par[u] = find_par(par[u]);
}
bool dd[maxn];
void dsu(long long x, long long y) {
  x = find_par(x);
  y = find_par(y);
  if (x == y) return;
  par[x] = y;
  siz[y] += siz[x];
}
bool dfs(long long u) {
  col[u] = 1;
  for (auto to : adj[u]) {
    if (col[to] == 1) return false;
    if (col[to] == 2) continue;
    if (!dfs(to)) return false;
  }
  col[u] = 2;
  return true;
}
bool kt[maxn];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  if (fopen("248.in", "r")) {
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
  }
  long long n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    siz[i] = 1;
    par[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    long long x, y;
    cin >> x >> y;
    adj[x].push_back(y);
    dsu(x, y);
  }
  long long ans = n;
  for (int i = 1; i <= n; i++) {
    long long p = find_par(i);
    if (!kt[p] && col[i] == 0) {
      if (dfs(i)) continue;
      kt[p] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (i == find_par(i)) {
      if (!kt[find_par(i)]) ans--;
    }
  }
  cout << ans;
}
