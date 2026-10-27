#include <bits/stdc++.h>
using namespace std;
int num[200005];
map<int, int, greater<int> > pts;
void remove(map<int, int, greater<int> >::iterator it) {
  if (it->second == 1)
    pts.erase(it);
  else
    it->second--;
}
int main() {
  int n, d;
  scanf("%d %d", &n, &d);
  for (int i = (1); i <= (n); i++) {
    scanf("%d", &num[i]);
  }
  for (int i = (1); i <= (n); i++) {
    int t;
    scanf("%d", &t);
    pts[t]++;
  }
  int mx = num[d] + pts.begin()->first;
  remove(pts.begin());
  int ans = 0;
  for (int i = (d - 1); i >= (1); i--) {
    auto it = pts.lower_bound(mx - num[i]);
    if (it != pts.end()) {
      remove(it);
    } else {
      remove(pts.begin());
      ++ans;
    }
  }
  printf("%d\n", ans + 1);
  return 0;
}
