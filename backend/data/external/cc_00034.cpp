#include <bits/stdc++.h>
using namespace std;
int a[5010], b[5010], w[5010], x[5010], y[5010], z[5010];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) a[i] = 1000000000;
  memset(b, 0, sizeof(b));
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d%d", &w[i], &x[i], &y[i], &z[i]);
    x[i]--;
    y[i]--;
    if (w[i] == 1) {
      for (int j = x[i]; j <= y[i]; j++) b[j] += z[i];
    } else {
      for (int j = x[i]; j <= y[i]; j++) a[j] = min(a[j], z[i] - b[j]);
    }
  }
  for (int i = 0; i < n; i++) b[i] = a[i];
  for (int i = 0; i < m; i++)
    if (w[i] == 1) {
      for (int j = x[i]; j <= y[i]; j++) b[j] += z[i];
    } else {
      int can = 0;
      for (int j = x[i]; j <= y[i]; j++)
        if (b[j] == z[i]) {
          can = 1;
          break;
        }
      if (!can) {
        puts("NO");
        return 0;
      }
    }
  puts("YES");
  for (int i = 0; i < n; i++) {
    printf("%d", a[i]);
    if (i + 1 == n)
      puts("");
    else
      printf(" ");
  }
  return 0;
}
