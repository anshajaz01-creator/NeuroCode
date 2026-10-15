#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  string s;
  cin >> n >> s;
  vector<int> zog, frd;
  for (int i = 0; i < (int)(n); ++i) {
    if (i % 2 == 0 && s[i] != 'r')
      zog.push_back(s[i]);
    else if (i % 2 != 0 && s[i] != 'b')
      frd.push_back(s[i]);
  }
  long long x1 = 0, x2 = 0;
  x1 = min(zog.size(), frd.size()) + max(zog.size(), frd.size()) -
       min(zog.size(), frd.size());
  zog.clear();
  frd.clear();
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0 && s[i] != 'b')
      zog.push_back(s[i]);
    else if (i % 2 != 0 && s[i] != 'r')
      frd.push_back(s[i]);
  }
  x2 = min(zog.size(), frd.size()) + max(zog.size(), frd.size()) -
       min(zog.size(), frd.size());
  cout << min(x1, x2);
  return 0;
}
