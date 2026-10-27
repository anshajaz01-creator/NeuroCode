#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& a) {
  os << "{";
  for (size_t i = 0; i < a.size(); ++i) os << (i > 0 ? "," : "") << a[i];
  return os << "}";
}
[[maybe_unused]] constexpr ll MOD = 1e9 + 7;
[[maybe_unused]] constexpr int INF = 0x3f3f3f3f;
[[maybe_unused]] constexpr ll INFL = 0x3f3f3f3f3f3f3f3fLL;
int main() {
  int n, q;
  cin >> n >> q;
  vector<int> bit(32);
  for (int i = 0; i < (n); ++i) {
    int a;
    cin >> a;
    for (int j = 0; j < (32); ++j) {
      if (a >> j & 1) bit[j]++;
    }
  }
  for (int i = 0; i < (q); ++i) {
    int a;
    cin >> a;
    vector<int> tmp(bit);
    int ans = 0;
    for (int j = (32) - 1; 0 <= j; --j) {
      int v = 1 << j;
      if (a >= v) {
        int d = min(a / v, bit[j]);
        ans += d;
        a -= d * v;
      }
    }
    if (a != 0)
      cout << -1 << '\n';
    else
      cout << ans << '\n';
  }
  return 0;
}
