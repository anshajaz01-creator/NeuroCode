#include <bits/stdc++.h>
using namespace std;
int32_t main() {
  ios_base::sync_with_stdio(false);
  long long n, m, k;
  cin >> n >> m >> k;
  vector<long long> p(n), s(n), c(k);
  for (auto& i : p) {
    cin >> i;
  }
  vector<vector<pair<long long, long long>>> sch(n);
  for (long long i = 0; i < n; i++) {
    cin >> s[i];
    sch[--s[i]].push_back({p[i], i});
  }
  vector<long long> is_the_best(n, false);
  for (long long i = 0; i < n; i++) {
    if (sch[i].empty()) continue;
    auto mx = *max_element(sch[i].begin(), sch[i].end());
    is_the_best[mx.second] = true;
  }
  long long ans = 0;
  while (k--) {
    long long q;
    cin >> q;
    ans += !is_the_best[q - 1];
  }
  cout << ans;
  return 0;
}
