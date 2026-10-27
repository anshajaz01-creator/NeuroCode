#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 5;
int n, m, d;
int l[maxn], ans[maxn];
int main() {
  scanf("%d%d%d", &n, &m, &d);
  int sum = 0, remain;
  for (register int i = 1; i <= m; ++i) {
    scanf("%d", &l[i]);
    sum += l[i];
  }
  remain = n - sum;
  if (sum == 0 || remain > (d - 1) * (m + 1)) {
    printf("NO\n");
    return 0;
  }
  int pos = 0;
  int i = 1;
  while (pos < n) {
    if (remain < d - 1) {
      pos += remain + 1, remain = 0;
      for (register int j = 0; j <= l[i] - 1; ++j) ans[pos + j] = i;
      pos += l[i] - 1, i++;
    } else {
      pos += d, remain -= d - 1;
      for (register int j = 0; j <= l[i] - 1; ++j) ans[pos + j] = i;
      pos += l[i] - 1, i++;
    }
  }
  printf("YES\n");
  for (register int i = 1; i <= n; ++i) printf("%d ", ans[i]);
  return 0;
}
