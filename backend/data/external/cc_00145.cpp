#include <bits/stdc++.h>
int ll[1009];
bool map[109][109];
int main() {
  int n, len;
  memset(map, 0, sizeof(map));
  scanf("%d%d", &n, &len);
  int i2 = (len + 1) / 2;
  int j2 = (len + 1) / 2;
  int i, j;
  for (i = 1; i <= n; i++) {
    scanf("%d", &ll[i]);
  }
  int k, p;
  for (k = 1; k <= n; k++) {
    int min = 99999999;
    int ri, rj;
    for (i = 1; i <= len; i++) {
      for (j = 1; j <= len; j++) {
        if (j + ll[k] - 1 > len) break;
        int ok = 0;
        for (p = 0; p < ll[k]; p++) {
          if (map[i][j + p] == 1) {
            j = j + p;
            ok = 1;
            break;
          }
        }
        if (ok == 0) {
          int all = 0;
          if (j + ll[k] - 1 <= j2) {
            all =
                (2 * j2 - 2 * j - ll[k] + 1) * ll[k] / 2 + abs(i - i2) * ll[k];
          } else if (j >= j2) {
            all =
                (2 * j - 2 * j2 + ll[k] - 1) * ll[k] / 2 + abs(i - i2) * ll[k];
          } else {
            all = (j2 - j) * (j2 - j + 1) / 2 +
                  (j + ll[k] - 1 - j2) * (j + ll[k] - j2) / 2 +
                  abs(i - i2) * ll[k];
          }
          if (min > all) {
            min = all;
            ri = i;
            rj = j;
          }
        }
      }
    }
    if (min == 99999999) {
      printf("-1\n");
    } else {
      printf("%d %d %d\n", ri, rj, rj + ll[k] - 1);
      for (p = 0; p < ll[k]; p++) {
        map[ri][rj + p] = 1;
      }
    }
  }
}
