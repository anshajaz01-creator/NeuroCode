#include <bits/stdc++.h>
using namespace std;
int64_t s[200000 + 3];
signed main() {
  int64_t n, d;
  cin >> n >> d;
  for (int64_t i = 1; i <= n; ++i) {
    cin >> s[i];
  }
  map<int64_t, int64_t> mm;
  for (int64_t i = 1; i <= n; ++i) {
    int64_t va;
    cin >> va;
    mm[va]++;
  }
  int64_t pos = s[d] + (mm.rbegin()->first);
  mm.rbegin()->second -= 1;
  if ((mm.rbegin()->second) == 0) {
    mm.erase(mm.find(mm.rbegin()->first));
  }
  int64_t rank = 0;
  for (int64_t i = 1; i <= n; ++i) {
    if (i != d) {
      if (s[i] + (mm.begin()->first) <= pos) {
        mm.begin()->second -= 1;
        if ((mm.begin()->second) == 0) {
          mm.erase(mm.begin());
        }
      } else {
        rank++;
        mm.rbegin()->second -= 1;
        if ((mm.rbegin()->second) == 0) {
          mm.erase(mm.find(mm.rbegin()->first));
        }
      }
    }
  }
  printf("%lld\n", rank + 1);
  return 0;
}
