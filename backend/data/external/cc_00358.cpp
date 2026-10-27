#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
void solve() {
  long long n, x, m;
  cin >> n >> x >> m;
  long long L, R;
  bool found = false;
  while (m--) {
    long long l, r;
    cin >> l >> r;
    if (l <= x and x <= r and !found) {
      found = true;
      L = l;
      R = r;
      continue;
    }
    if (!found) continue;
    if (L <= l and r <= R) continue;
    if (l <= L and R <= r) {
      L = l;
      R = r;
      continue;
    }
    vector<pair<long long, long long>> v = {{L, R}, {l, r}};
    sort(v.begin(), v.end());
    if (v[1].first <= v[0].second) {
      L = v[0].first;
      R = v[1].second;
    }
  }
  if (!found)
    cout << 1 << '\n';
  else
    cout << R - L + 1 << '\n';
}
void solve(bool testcase) {
  long long t;
  cin >> t;
  while (t--) solve();
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve(true);
  return 0;
}
