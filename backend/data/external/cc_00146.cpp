#include <bits/stdc++.h>
int main() {
  int n, m;
  int a[99][99];
  while (scanf("%d%d", &n, &m) == 2) {
    memset(a, 0, sizeof(a));
    while (n--) {
      int x, bestx = -1, besty = -1, min = 999999999;
      scanf("%d", &x);
      for (int i = 0; i < m; i++)
        for (int j = 0; j <= m - x; j++) {
          int ok = 1, cost = 0;
          for (int k = 0; k < x && ok; k++)
            if (a[i][j + k])
              ok = 0;
            else
              cost += abs(i - (m >> 1)) + abs(j + k - (m >> 1));
          if (ok && min > cost) {
            min = cost;
            bestx = i;
            besty = j;
          }
        }
      if (bestx >= 0) {
        printf("%d %d %d\n", bestx + 1, besty + 1, besty + x);
        for (int j = besty; j < besty + x; j++) a[bestx][j] = 1;
      } else
        puts("-1");
    }
  }
}
