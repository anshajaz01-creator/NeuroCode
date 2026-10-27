#include <bits/stdc++.h>
const int maxn = int(2e5) + 7;
int n, k, a[maxn];
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  long long ans = 0;
  for (int i = n; i >= 1; i--) {
    int cnt = a[i] / k, res = a[i] % k;
    ans += cnt + bool(res);
    if (res) a[i - 1] -= std::min(a[i - 1], k - res);
  }
  printf("%lld\n", ans);
  return 0;
}
