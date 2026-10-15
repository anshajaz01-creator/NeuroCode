#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, ans = 0;
  scanf("%I64d", &n);
  for (long long i = 2; i <= n; ++i) {
    long long up = n / i;
    if (up < 2) break;
    ans += (2 + up) * (up - 1) * 2;
  }
  printf("%I64d\n", ans);
  return 0;
}
