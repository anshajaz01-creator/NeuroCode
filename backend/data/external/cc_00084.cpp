#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lint = long long;
using pii = pair<int, int>;
const int N = 200005;
int n, q, a[N], ind[N], ps[N], pe[N], pc, dep[N], cyc[N], cn[N], csz[N], cc;
vector<int> e[N], dv[N];
vector<vector<vector<int>>> cv;
queue<int> qq;
void f(int first, int second, int z, int u, int v, int w) {
  dep[first] = z;
  ps[first] = ++pc;
  dv[dep[first]].push_back(pc);
  cv[u][(v + dep[first]) % w].push_back(dep[first]);
  for (int i : e[first])
    if (i != first) f(i, first, z + 1, u, v, w);
  pe[first] = pc;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ind[a[i]]++;
  }
  for (int i = 1; i <= n; i++)
    if (!ind[i]) qq.push(i);
  while (!qq.empty()) {
    int first = qq.front();
    qq.pop();
    e[a[first]].push_back(first);
    if (--ind[a[first]] == 0) qq.push(a[first]);
  }
  cv.push_back(vector<vector<int>>());
  for (int i = 1; i <= n; i++)
    if (ind[i]) {
      if (!cyc[i]) {
        cyc[i] = ++cc;
        cv.push_back(vector<vector<int>>());
        cv[cc].push_back(vector<int>());
        int zz = 1;
        for (int j = a[i]; j != i; j = a[j], zz++) {
          cyc[j] = cc;
          cv[cc].push_back(vector<int>());
        }
        int z = zz;
        csz[i] = zz;
        cn[i] = --z;
        for (int j = a[i]; j != i; j = a[j]) {
          csz[j] = zz;
          cn[j] = --z;
        }
      }
      f(i, 0, 0, cyc[i], cn[i], csz[i]);
    }
  for (auto &i : cv)
    for (auto &j : i) sort(j.begin(), j.end());
  cin >> q;
  for (; q--;) {
    ll m;
    int second;
    cin >> m >> second;
    if (cyc[second]) {
      int idx = (cn[second] + m) % csz[second];
      m = min(m, ll(1e6));
      auto &cur = cv[cyc[second]][idx];
      cout << int(upper_bound(cur.begin(), cur.end(), m) - cur.begin()) << '\n';
    } else {
      ll t = dep[second] + m;
      if (t >= N)
        cout << "0\n";
      else
        cout << int(upper_bound(dv[t].begin(), dv[t].end(), pe[second]) -
                    lower_bound(dv[t].begin(), dv[t].end(), ps[second]))
             << '\n';
    }
  }
}
