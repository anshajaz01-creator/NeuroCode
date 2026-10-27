#include <bits/stdc++.h>
using namespace std;
long long f[300005], ans, a[300005], b[300005], sum1[300005], sum2[300005],
    t1[300005], t2[300005], t3[300005], t4[300005], n;
int main() {
  scanf("%lld", &n);
  for (long long i = 1; i <= n; i++) scanf("%lld", &a[i]);
  for (long long i = n; i; i--)
    t2[i] = t2[i + 1] + a[i] * (2ll * n - i), sum1[i] = sum1[i + 1] + a[i],
    t1[i] += t1[i + 1] + a[i] * (i - 1);
  for (long long i = 1; i <= n; i++) scanf("%lld", &b[i]);
  for (long long i = n; i; i--)
    t4[i] = t4[i + 1] + b[i] * (2ll * n - i), sum2[i] = sum2[i + 1] + b[i],
    t3[i] += t3[i + 1] + b[i] * (i - 1);
  f[0] = 0;
  ans = t1[1] + t4[1];
  for (long long i = 1; i <= n; i++) {
    if (i & 1) {
      f[i] = f[i - 1] + a[i] * ((i << 1) - 2) + b[i] * ((i << 1) - 1);
      ans = max(ans,
                f[i] + i * (sum1[i + 1] + sum2[i + 1]) + t2[i + 1] + t3[i + 1]);
    } else {
      f[i] = f[i - 1] + a[i] * ((i << 1) - 1) + b[i] * ((i << 1) - 2);
      ans = max(ans,
                f[i] + i * (sum1[i + 1] + sum2[i + 1]) + t1[i + 1] + t4[i + 1]);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
