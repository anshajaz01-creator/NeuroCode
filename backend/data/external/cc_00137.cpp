#include <bits/stdc++.h>
using namespace std;
int main() {
  int cnt1, cnt2, x, y;
  while (~scanf("%d%d%d%d", &cnt1, &cnt2, &x, &y)) {
    long long l = 0, r = 0x3f3f3f3f3f3f;
    while (l <= r) {
      long long mid = (l + r) >> 1;
      if (cnt1 <= mid - mid / x && cnt2 <= mid - mid / y &&
          cnt1 + cnt2 <= mid - mid / (x * y))
        r = mid - 1;
      else
        l = mid + 1;
    }
    printf("%I64d\n", l);
  }
  return 0;
}
