#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  int k;
  cin >> s >> k;
  s = s + "#";
  int ans = 0;
  while (k--) {
    string tmp;
    cin >> tmp;
    int l = 0;
    int r = 0;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == tmp[0])
        l++;
      else if (s[i] == tmp[1])
        r++;
      else {
        ans += min(l, r);
        l = r = 0;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
