#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7, siz = 1e6 + 5;
long long t, n, m, k, a[siz];
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (long long i = 1; i <= n; i++) cin >> a[i];
  long long ans = 0;
  vector<long long> out;
  for (long long i = 1; i < n; i++) {
    long long d = 1;
    while (i + d <= n) d *= 2;
    d /= 2;
    a[i + d] += a[i];
    out.push_back(a[i] + (out.size() == 0 ? 0 : out.back()));
  }
  for (auto x : out) cout << x << "\n";
}
