#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
char s[100001];
int slen;
bool ok(int lastdash, int lastval) {
  if (lastval < 1) return false;
  int cur = 0;
  for (int i = (0); i < (slen); ++i) {
    if (s[i] == '(') ++cur;
    if (s[i] == ')' || s[i] == '#' && i != lastdash) --cur;
    if (i == lastdash) cur -= lastval;
    if (cur < 0) return false;
  }
  return cur == 0;
}
void run() {
  scanf("%s", s);
  slen = strlen(s);
  int nopen = 0, nclose = 0, ndash = 0, lastdash = -1;
  for (int i = (0); i < (slen); ++i)
    if (s[i] == '(')
      ++nopen;
    else if (s[i] == ')')
      ++nclose;
    else
      ++ndash, lastdash = i;
  int lastval = nopen - nclose - (ndash - 1);
  if (ok(lastdash, lastval)) {
    for (int i = (0); i < (ndash); ++i)
      printf("%d\n", i != ndash - 1 ? 1 : lastval);
  } else {
    printf("-1\n");
  }
}
int main() {
  run();
  return 0;
}
