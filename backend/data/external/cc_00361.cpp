#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  ;
  long long int t;
  cin >> t;
  while (t--) {
    long long int n, x, m;
    cin >> n >> x >> m;
    long long int prel = x;
    long long int prer = x;
    long long int ans = 1;
    map<long long int, long long int> mp;
    long long int f = 0;
    for (long long int i = 0; i < m; i++) {
      long long int l, r;
      cin >> l >> r;
      if ((prel >= l && prel <= r) || (prer >= l && prer <= r)) {
        if (f == 0) {
          f++;
          ans += abs(r - l);
          mp[l]++;
          mp[r]++;
          prel = l;
          prer = r;
        } else {
          if (prel > l) {
            ans += abs(l - prel);
          }
          if (prer < r) {
            ans += abs(r - prer);
          }
        }
        prel = min(prel, l);
        prer = max(prer, r);
      }
    }
    cout << ans << "\n";
  }
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
