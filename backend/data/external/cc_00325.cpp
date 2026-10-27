#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, i, cntb, cntr, cntm, ans;
  string s;
  cntb = cntr = 0;
  cin >> n >> s;
  for (i = (0); i < (n); ++i) {
    if (i & 1) {
      if (s[i] == 'b') {
        cntb++;
      }
    } else {
      if (s[i] == 'r') {
        cntr++;
      }
    }
  }
  cntm = min(cntb, cntr);
  cntb -= cntm;
  cntr -= cntm;
  ans = cntm + cntb + cntr;
  cntb = cntr = 0;
  for (i = (0); i < (n); ++i) {
    if (i & 1) {
      if (s[i] == 'r') {
        cntr++;
      }
    } else {
      if (s[i] == 'b') {
        cntb++;
      }
    }
  }
  cntm = min(cntb, cntr);
  cntb -= cntm;
  cntr -= cntm;
  ans = min(ans, cntm + cntb + cntr);
  cout << ans << endl;
}
