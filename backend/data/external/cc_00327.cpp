#include <bits/stdc++.h>
using namespace std;
const int mod = 7 + (int)1e9;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  string s;
  cin >> s;
  int evenr = 0;
  int oddr = 0;
  int evenb = 0;
  int oddb = 0;
  for (int i = 0; i < n; i++) {
    char cur = s[i];
    if (i % 2 == 0) {
      if (cur == 'r')
        evenr++;
      else
        evenb++;
    } else {
      if (cur == 'r')
        oddr++;
      else
        oddb++;
    }
  }
  int ans = n;
  ans = min(ans, max(evenb, oddr));
  ans = min(ans, max(evenr, oddb));
  cout << ans;
  return 0;
}
