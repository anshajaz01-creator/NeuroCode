#include <bits/stdc++.h>
using namespace std;
string s;
int l, r, D;
int main() {
  cin >> s;
  for (int i = 0, sz = s.size(); i < sz; i++) {
    if (s[i] == '(')
      l++, r++;
    else {
      l--;
      if (r > 0) r--;
      if (l < 0) cout << -1, exit(0);
      if (s[i] == '#') r = 0, D++;
    }
  }
  if (r > 0) cout << -1, exit(0);
  for (int i = 0; i < D - 1; i++) cout << 1 << endl;
  cout << l + 1;
}
