#include <bits/stdc++.h>
using namespace std;
int a[100005], Log[100005], i, t, n;
long long ans;
int main() {
  scanf("%d", &n);
  for (i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (i = 1; (1 << i) <= n; i++) Log[1 << i] = i;
  for (i = 3; i <= n; i++)
    if (!Log[i]) Log[i] = Log[i - 1];
  for (i = 1; i < n; printf("%I64d\n", ans), i++)
    if (a[i] > 0) t = Log[n - i], ans += a[i], a[i + (1 << t)] += a[i];
}
