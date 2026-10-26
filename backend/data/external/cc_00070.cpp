#include <bits/stdc++.h>
using namespace std;
string s;
int l, _, p, t;
int main() {
  ios ::sync_with_stdio(false);
  cin >> s;
  for (register int i = 0; i < s.size(); i++) {
    if (s[i] == '(') l++;
    if (s[i] == ')') l--;
    if (s[i] == '#') l--, _++;
    if (l < 0) {
      cout << -1;
      return 0;
    }
  }
  for (register int i = 0; i < s.size(); i++) {
    if (s[i] == '#') {
      t++;
      if (t == _) p -= l;
      p--;
    }
    if (s[i] == '(') p++;
    if (s[i] == ')') p--;
    if (p < 0) {
      cout << "-1";
      return 0;
    }
  }
  for (register int i = 1; i < _; i++) cout << "1\n";
  cout << 1 + l;
  return 0;
}
