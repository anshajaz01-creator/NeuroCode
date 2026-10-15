#include <bits/stdc++.h>
using namespace std;
inline long long mul(long long x, long long y, long long m) {
  long long z = 1LL * x * y;
  if (z >= m) z %= m;
  return z;
}
inline long long add(long long x, long long y, long long m) {
  long long z = x + y;
  if (z >= m) z %= m;
  return z;
}
inline long long sub(long long x, long long y, long long m) {
  long long z = x - y;
  if (z < 0) z += m;
  z %= m;
  return z;
}
vector<long long> adj[300050];
long long a[300050], n, m;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long u, v;
  cin >> n >> m;
  for (long long i = 0; i < n; i++) cin >> a[i];
  for (long long i = 0; i < m; i++) cin >> u >> v, adj[v].push_back(u);
  set<long long> s;
  for (long long i = 0; i < adj[a[n - 1]].size(); i++)
    s.insert(adj[a[n - 1]][i]);
  long long cp = n - 2;
  long long ans = 0;
  while (cp >= 0) {
    if (s.empty()) break;
    long long k = a[cp];
    cp--;
    if (s.find(k) != s.end()) {
      ans++;
      continue;
    }
    set<long long> s1;
    for (long long i = 0; i < adj[k].size(); i++) {
      long long x = adj[k][i];
      if (s.find(x) != s.end()) s1.insert(x);
    }
    s = s1;
  }
  cout << ans;
  return 0;
}
