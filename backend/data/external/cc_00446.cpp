#include <bits/stdc++.h>
inline int pidorand() { return ((rand() & 32767) << 15) | (rand() & 32767); }
using namespace std;
inline int nxt() {
  int x;
  scanf("%d", &x);
  return x;
}
int main() {
  int n = nxt(), m = nxt();
  int n_l = nxt(), n_e = nxt();
  int v = nxt();
  vector<int> ls(n_l);
  vector<int> es(n_e);
  for (int i = 0; i < n_l; ++i) {
    ls[i] = nxt();
  }
  for (int i = 0; i < n_e; ++i) {
    es[i] = nxt();
  }
  int q = nxt();
  while (q--) {
    int x1 = nxt(), y1 = nxt(), x2 = nxt(), y2 = nxt();
    if (x1 == x2) {
      printf("%d\n", abs(y1 - y2));
      continue;
    }
    int ans = 1e9;
    if (y1 > y2) {
      swap(y1, y2);
    }
    if (n_l) {
      auto it = lower_bound((ls).begin(), (ls).end(), y1);
      int opt = 1e9;
      if (it != ls.end()) {
        opt = min(opt, abs(*it - y1) + abs(*it - y2));
      }
      if (it != ls.begin()) {
        --it;
        opt = min(opt, abs(*it - y1) + abs(*it - y2));
      }
      ans = min(ans, abs(x1 - x2) + opt);
    }
    if (n_e) {
      auto it = lower_bound((es).begin(), (es).end(), y1);
      int opt = 1e9;
      if (it != es.end()) {
        opt = min(opt, abs(*it - y1) + abs(*it - y2));
      }
      if (it != es.begin()) {
        --it;
        opt = min(opt, abs(*it - y1) + abs(*it - y2));
      }
      ans = min(ans, (abs(x1 - x2) + v - 1) / v + opt);
    }
    printf("%d\n", ans);
  }
  return 0;
}
