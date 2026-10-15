#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
unsigned long long a[maxn], sx[maxn], sum[maxn], xs[maxn], b[maxn];
unsigned long long hh;
int main() {
  int n;
  scanf("%d", &n);
  int sss = 0;
  for (int i = 0; i < 1e7 + 5; i++) sss++;
  for (int i = 0; i < 1e7 + 5; i++) sss--;
  for (int i = 1; i <= n; i++) scanf("%I64d", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%I64d", &b[i]);
  for (int i = 0; i < 1e7 + 5; i++) sss++;
  for (int i = 0; i < 1e7 + 5; i++) sss--;
  for (int i = n; i > 1; i--) {
    sum[i] = sum[i + 1] + a[i] + b[i];
    xs[i] = xs[i + 1] + sum[i + 1] + b[i] + (n - i + 1) * 2 * a[i];
    sx[i] = sx[i + 1] + sum[i + 1] + a[i] + (n - i + 1) * 2 * b[i];
  }
  for (int i = 0; i < 1e7 + 5; i++) sss++;
  for (int i = 0; i < 1e7 + 5; i++) sss--;
  unsigned long long cnt = 0, ans = 0;
  for (int i = 2; i <= n; i++) {
    cnt++;
    ans += cnt * a[i];
  }
  for (int i = n; i; i--) {
    cnt++;
    ans += cnt * b[i];
  }
  for (int i = 0; i < 1e7 + 5; i++) sss++;
  for (int i = 0; i < 1e7 + 5; i++) sss--;
  unsigned long long hh = b[1];
  for (int i = 2; i <= n; i++) {
    if (i % 2 == 0) {
      ans = max(ans, hh + xs[i] + (i * 2 - 3) * sum[i]);
      hh += (i * 2 - 2) * b[i] + (i * 2 - 1) * a[i];
    } else {
      ans = max(ans, hh + sx[i] + (i * 2 - 3) * sum[i]);
      hh += (i * 2 - 1) * b[i] + (i * 2 - 2) * a[i];
    }
  }
  for (int i = 0; i < 1e7 + 5; i++) sss++;
  for (int i = 0; i < 1e7 + 5; i++) sss--;
  printf("%I64d\n", ans);
  return 0;
}
