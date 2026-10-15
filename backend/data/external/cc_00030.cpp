#include <bits/stdc++.h>
const double eps = 1e-9;
const int int_inf = 2000000000;
const long long i64_inf = 1000000000000000000LL;
const double pi = acos(-1.0);
using namespace std;
int wa[1000010];
int wb[1000010];
int a[1000100];
int b[1000100];
int la, lb;
int res = 0;
int main() {
  memset(wa, -1, sizeof(wa));
  memset(wb, -1, sizeof(wb));
  cin >> la >> lb;
  for (int i = 0; i < (int)la; i++) scanf("%d", &a[i]), wa[a[i]] = i;
  for (int i = 0; i < (int)lb; i++) scanf("%d", &b[i]), wb[b[i]] = i;
  int first, last, len = 0;
  for (int i = 0; i < (int)la; i++) {
    if (len == 0) {
      if (wb[a[i]] == -1) continue;
      first = last = wb[a[i]];
      len = 1;
    } else {
      len--;
      first = wb[a[i]];
      if (first == -1) {
        len = 0;
        continue;
      }
    }
    int j = (i + len) % la;
    while (j != i) {
      if (wb[a[j]] == -1) break;
      if (first <= last)
        if (wb[a[j]] > last || wb[a[j]] < first) {
          last = wb[a[j]];
          len++;
          j = (j + 1) % la;
          continue;
        } else
          break;
      if (wb[a[j]] > last && wb[a[j]] < first) {
        last = wb[a[j]];
        len++;
        j = (j + 1) % la;
        continue;
      } else
        break;
    }
    res = max(res, len);
  }
  cout << res << endl;
  return 0;
}
