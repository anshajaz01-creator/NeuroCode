#include <bits/stdc++.h>
using namespace std;
using std::ios;
constexpr int MOD = 1e9 + 7;
constexpr int mod = 998244353;
template <typename T>
T power(T a, T b) {
  T r = 1;
  while (b) {
    if (b & 1) r *= a;
    b /= 2;
    a *= a;
  }
  return r;
}
const int mxn = 1e5 + 5;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  ;
  int tt = 1;
  while (tt--) {
    int n;
    cin >> n;
    vector<int> a(n), b;
    for (int &v : a) cin >> v;
    string s;
    b.push_back(0);
    int l = 0, r = n - 1;
    while (l < r && l < n && r >= 0) {
      if (a[l] < a[r] && a[l] > b.back()) {
        b.push_back(a[l]);
        s.push_back('L');
        l++;
      } else if (a[r] < a[l] && a[r] > b.back()) {
        b.push_back(a[r]);
        s.push_back('R');
        r--;
      } else if (a[l] == a[r]) {
        int lc = 1, rc = 1, rs = r - 1;
        for (int i = 1; i + l < n; i++) {
          if (a[l + i] > a[l + i - 1])
            lc++;
          else
            break;
        }
        while (rs >= 0 && a[rs] > a[rs + 1]) {
          rc++;
          rs--;
        }
        if (rc > lc && a[r] > b.back()) {
          b.push_back(a[r]);
          s.push_back('R');
          r--;
        } else if (lc >= rc && a[l] > b.back()) {
          b.push_back(a[l]);
          s.push_back('L');
          l++;
        } else
          break;
      } else
        break;
    }
    while (l < n && a[l] > b.back()) {
      b.push_back(a[l]);
      s.push_back('L');
      l++;
    }
    while (r >= 0 && a[r] > b.back()) {
      b.push_back(a[r]);
      s.push_back('R');
      r--;
    }
    cout << s.size() << '\n' << s;
  }
}
