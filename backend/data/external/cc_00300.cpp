#include <bits/stdc++.h>
using namespace std;
template <typename... Args>
void read(Args &...args) {
  ((cin >> args), ...);
}
template <typename... Args>
void show(Args... args) {
  ((cout << args << " "), ...);
}
void solve() {
  int n;
  read(n);
  vector<int> v(n);
  for (auto &it : v) cin >> it;
  int l = 0, r = n - 1, x = 0;
  string s;
  while (l <= r) {
    if (min(v[l], v[r]) > x) {
      if (v[l] < v[r]) {
        s.push_back('L');
        x = v[l++];
      } else if (v[r] < v[l]) {
        s.push_back('R');
        x = v[r--];
      } else {
        int ll = l + 1, rr = r - 1;
        while (ll < r && v[ll] > v[ll - 1]) ll++;
        while (rr > l && v[rr] > v[rr + 1]) rr--;
        if (ll - l > r - rr) {
          x = ll - l;
          while (x--) s.push_back('L');
        } else {
          x = r - rr;
          while (x--) s.push_back('R');
        }
        break;
      }
    } else if (max(v[l], v[r]) > x) {
      if (v[l] > v[r]) {
        s.push_back('L');
        x = v[l++];
      } else {
        s.push_back('R');
        x = v[r--];
      }
    } else {
      break;
    }
  }
  cout << int(s.size()) << '\n' << s;
}
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = 1;
  while (T--) solve();
  return 0;
}
