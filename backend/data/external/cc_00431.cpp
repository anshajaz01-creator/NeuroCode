#include <bits/stdc++.h>
using namespace std;
const long long MAXN = 2e5 + 21, inf = 1e9 + 21;
int n, m;
int x[MAXN], s[MAXN];
map<int, int> mp;
inline int gr(int p, int l) { return *(upper_bound(s, s + n, p + l) - 1); }
inline int gl(int p, int l) { return *lower_bound(s, s + n, p - l); }
inline int solve(int p, int l) {
  int rc = gr(p, l);
  int lc = gl(rc, l - rc + p);
  int tmp = (2 * rc) - p - lc;
  if (rc == lc && p == rc) return rc;
  if (lc == p)
    return solve(lc, l % tmp);
  else
    return solve(lc, l - tmp);
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> x[i];
    s[i] = x[i];
    mp[x[i]] = i + 1;
  }
  sort(s, s + n);
  while (m--) {
    int a, l, t;
    cin >> a >> l;
    t = solve(x[--a], l);
    cout << mp[t] << '\n';
  }
  return 0;
}
