#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const long long mod = 1e9 + 7;
const double pi = acos(-1);
vector<vector<int> > adj(N);
map<pair<int, int>, bool> mp, vis;
pair<int, int> f(int x, int y) { return {min(x, y), max(x, y)}; }
bool sa5eef[N];
int dfs(int u) {
  int ret = -1;
  vector<int> meh;
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (mp[f(u, v)]) continue;
    meh.push_back(v);
    mp[f(u, v)] = 1;
  }
  for (int i = 0; i < meh.size(); i++) {
    int v = meh[i];
    if (sa5eef[v]) continue;
    int p = dfs(v);
    if (p != -1) {
      printf("%d %d %d\n", u, v, p);
      vis[f(u, v)] = vis[f(v, p)] = 1;
    }
  }
  for (int i = 0; i < meh.size(); i++) {
    int v = meh[i];
    if (!vis[f(u, v)]) {
      if (ret == -1)
        ret = v;
      else {
        printf("%d %d %d\n", v, u, ret);
        ret = -1;
      }
    }
  }
  sa5eef[u] = 1;
  return ret;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int x, y;
  int cntr = 1;
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &x, &y);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  if (m % 2)
    puts("No solution");
  else
    dfs(1);
  return 0;
}
long long fastpow(long long b, long long e) {
  if (!e) return 1;
  long long ret = fastpow(b, e / 2);
  ret = (ret * ret) % mod;
  if (e % 2) ret = (ret * b) % mod;
  return ret;
}
long long modinv(long long x) { return fastpow(x, mod - 2); }
double torad(double ang) { return ang * pi / 180.0; }
