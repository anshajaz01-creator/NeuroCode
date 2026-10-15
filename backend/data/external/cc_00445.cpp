#include <bits/stdc++.h>
using namespace std;
long long mx = 100000000000000000;
long long n, m, cl, ce, v;
vector<long long> stair, elevator;
long long go_elev(long long x1, long long y1, long long x2, long long y2) {
  long long ret = mx;
  if ((int)elevator.size() == 0) return ret;
  if (x1 == x2) return abs(y2 - y1);
  long long infront =
      lower_bound(elevator.begin(), elevator.end(), y1) - elevator.begin();
  if (infront != (int)elevator.size()) {
    long long temp = abs(elevator[infront] - y1);
    temp += abs(x2 - x1) / v;
    if (abs(x2 - x1) % v) temp++;
    temp += abs(elevator[infront] - y2);
    ret = min(ret, temp);
  }
  infront--;
  if (infront >= 0) {
    long long temp = abs(elevator[infront] - y1);
    temp += abs(x2 - x1) / v;
    if (abs(x2 - x1) % v) temp++;
    temp += abs(elevator[infront] - y2);
    ret = min(ret, temp);
  }
  return ret;
}
long long go_stair(long long x1, long long y1, long long x2, long long y2) {
  long long ret = mx;
  if ((int)stair.size() == 0) return ret;
  if (x1 == x2) return abs(y2 - y1);
  long long infront =
      lower_bound(stair.begin(), stair.end(), y1) - stair.begin();
  if (infront != (int)stair.size()) {
    long long temp = abs(stair[infront] - y1);
    temp += abs(x2 - x1);
    temp += abs(stair[infront] - y2);
    ret = min(ret, temp);
  }
  infront--;
  if (infront >= 0) {
    long long temp = abs(stair[infront] - y1);
    temp += abs(x2 - x1);
    temp += abs(stair[infront] - y2);
    ret = min(ret, temp);
  }
  return ret;
}
int main() {
  scanf("%lld %lld %lld", &n, &m, &cl);
  scanf("%lld %lld", &ce, &v);
  for (int i = 0; i < cl; i++) {
    long long a;
    scanf("%lld", &a);
    stair.push_back(a);
  }
  for (int i = 0; i < ce; i++) {
    long long a;
    scanf("%lld", &a);
    elevator.push_back(a);
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    long long x1, y1, x2, y2;
    scanf("%lld %lld", &x1, &y1);
    scanf("%lld %lld", &x2, &y2);
    long long ans = min(go_elev(x1, y1, x2, y2), go_elev(x2, y2, x1, y1));
    ans = min(ans, min(go_stair(x1, y1, x2, y2), go_stair(x2, y2, x1, y1)));
    printf("%lld\n", ans);
  }
  return 0;
}
