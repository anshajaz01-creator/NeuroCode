#include <bits/stdc++.h>
using namespace std;
int main() {
  long long k, d, t;
  scanf("%lld%lld%lld", &k, &d, &t);
  long long x = (k - 1) / d + 1;
  long long y = x * d + k;
  long long z = 2 * t / y;
  long long u = 2 * t - y * z;
  long long v = 2 * x * d * z + max(u, (u - k) << 1);
  printf("%lld.%c\n", v >> 1, "05"[v & 1]);
  return 0;
}
