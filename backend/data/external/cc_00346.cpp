#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 1e6 + 50;
long long a[maxn];
int main() {
  int n;
  long long k;
  scanf("%d%lld", &n, &k);
  long long ans = 0;
  long long pre = 0;
  for (int i = 0; i < n; i++) {
    if (pre) ans++;
    scanf("%lld", &a[i]);
    if (pre) a[i] -= (k - pre);
    if (a[i] > 0) {
      ans += (a[i] / k);
      pre = a[i] % k;
    } else
      pre = 0;
  }
  if (pre > 0) ans++;
  printf("%lld\n", ans);
}
