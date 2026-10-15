#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
inline void smax(int &x, int y) { x = max(x, y); }
inline void smin(int &x, int y) { x = min(x, y); }
ll gcd(ll a, ll b) { return ((b == 0) ? a : gcd(b, a % b)); }
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  int tcase;
  cin >> tcase;
  for (__typeof(tcase + 1) tc = (1) - ((1) > (tcase + 1));
       tc != (tcase + 1) - ((1) > (tcase + 1));
       tc += 1 - 2 * ((1) > (tcase + 1))) {
    int n;
    cin >> n;
    vector<int> v(n);
    for (__typeof(n) i = (0) - ((0) > (n)); i != (n) - ((0) > (n));
         i += 1 - 2 * ((0) > (n)))
      cin >> v[i];
    int g = 1, b = 0, s = 0;
    int st = -1;
    for (int i = 1; i < n; i++) {
      if (v[i] != v[i - 1]) {
        st = i;
        break;
      } else
        g++;
    }
    if (st == -1) {
      cout << 0 << " " << 0 << " " << 0 << "\n";
      continue;
    }
    vector<int> cnt;
    int cur = 1;
    for (int i = st + 1; i < n; i++) {
      if (v[i] != v[i - 1]) {
        cnt.push_back(cur);
        cur = 1;
      } else
        cur++;
    }
    cnt.push_back(cur);
    for (int i = 0; i < cnt.size(); i++) {
      if (s <= g) {
        s += cnt[i];
      } else {
        if (b <= g || 2 * (b + cnt[i] + s + g) <= n) {
          b += cnt[i];
        } else
          break;
      }
    }
    if (g < s && g < b && 2 * (b + s + g) <= n) {
      cout << g << " " << s << " " << b << "\n";
    } else {
      cout << 0 << " " << 0 << " " << 0 << "\n";
    }
  }
}
