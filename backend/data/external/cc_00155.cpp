#include <bits/stdc++.h>
using namespace std;
void solve() {
  int i, j = 0, r = 200, q, k = 1, d, y = 0, h, flag = 1, n, m = 0,
         a = 1000000007, b = 1000000007, h1, h2, a1, b1, a2, w, x, u, f, l, c,
         z;
  cin >> n >> k;
  m = 100005;
  vector<pair<int, int> > v[m + 1];
  for (i = 1; i < n + 1; i++) {
    cin >> a >> b;
    v[a].push_back({b, i});
  }
  vector<int> vp;
  set<pair<int, int> > st;
  for (i = 1; i < m; i++) {
    for (auto it : v[i]) st.insert(it);
    while (!st.empty() and st.begin()->first < i) st.erase(st.begin());
    while (st.size() > k) {
      auto it2 = *st.rbegin();
      vp.push_back(it2.second);
      st.erase(it2);
    }
  }
  sort(vp.begin(), vp.end());
  cout << vp.size() << endl;
  for (i = 0; i < vp.size(); i++) cout << vp[i] << " ";
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  while (t--) solve();
}
