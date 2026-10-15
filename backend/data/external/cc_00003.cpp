#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
vector<vector<pair<int, int> > > g;
set<pair<int, int> > good;
vector<char> very_good;
vector<int> d;
int k;
void check(long long int i) {
  while (!good.empty() && good.begin()->first < k) {
    int v = good.begin()->second;
    for (auto &y : g[v]) {
      int x = y.first;
      if (y.second >= i) continue;
      if (very_good[x]) {
        good.erase(make_pair(d[x], x));
        d[x]--;
        good.insert(make_pair(d[x], x));
      }
    }
    good.erase(make_pair(d[v], v));
    very_good[v] = false;
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m >> k;
  g.resize(n);
  d.resize(n);
  vector<pair<int, int> > f(m);
  for (int i = 0; i < m; ++i) {
    cin >> f[i].first >> f[i].second;
    f[i].first--, f[i].second--;
    g[f[i].first].push_back(make_pair(f[i].second, i));
    g[f[i].second].push_back(make_pair(f[i].first, i));
    d[f[i].first]++;
    d[f[i].second]++;
  }
  for (int i = 0; i < n; ++i) {
    good.insert(make_pair(d[i], i));
  }
  very_good.assign(n, true);
  check(1e18);
  vector<int> ans(m);
  for (int i = m - 1; i >= 0; --i) {
    ans[i] = good.size();
    int v = f[i].first, u = f[i].second;
    if (very_good[v] && very_good[u]) {
      good.erase(make_pair(d[v], v));
      d[v]--;
      good.insert(make_pair(d[v], v));
      good.erase(make_pair(d[u], u));
      d[u]--;
      good.insert(make_pair(d[u], u));
      check(i);
    }
  }
  for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
}
