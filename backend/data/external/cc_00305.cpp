#include <bits/stdc++.h>
using namespace std;
int a[1000 + 5];
int main() {
  int n, m, d, sum = 0;
  scanf("%d%d%d", &n, &m, &d);
  for (int i = 1; i <= m; i++) scanf("%d", a + i), sum += a[i];
  if (sum + (d - 1) * (m + 1) < n) return puts("NO"), 0;
  puts("YES");
  int l = 0, L = 1;
  for (int i = 1; i <= n; i++) {
    if (i - l == d || n - i + 1 == sum) {
      for (int j = 0; j < a[L]; j++) printf("%d ", L);
      l = i += a[L] - 1, sum -= a[L++];
    } else
      printf("0 ");
  }
  return 0;
}
