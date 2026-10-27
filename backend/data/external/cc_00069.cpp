#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse2")
using namespace std;
bool isPowerOfTwo(long long int x) { return x && (!(x & (x - 1))); }
void solve() {
  string str;
  cin >> str;
  long long int n = str.size(), count = 0, hash = 0;
  for (long long int i = 0; i < n; ++i) {
    if (count < 0) {
      cout << "-1\n";
      return;
    }
    if (str[i] == '(')
      count++;
    else if (str[i] == ')')
      count--;
    else
      hash++;
  }
  if (count >= hash) {
    long long int c = 0, x = 0;
    for (long long int i = 0; i < n; ++i) {
      if (c < 0) {
        cout << "-1\n";
        return;
      }
      if (str[i] == '(')
        c++;
      else if (str[i] == ')')
        c--;
      else {
        x++;
        if (x == hash)
          c -= (count - hash + 1);
        else
          c--;
      }
    }
    for (long long int i = 1; i < hash; ++i) cout << "1\n";
    cout << count - hash + 1;
  } else
    cout << "-1\n";
}
int32_t main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  while (T--) solve();
  return 0;
}
