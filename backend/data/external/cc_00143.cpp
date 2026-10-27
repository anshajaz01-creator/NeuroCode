#include <bits/stdc++.h>
using namespace std;
const int inf = 2e9;
bool vis[105][105];
int n, k;
int main() {
  scanf("%d%d", &n, &k);
  int x = (k + 1) / 2;
  int y = x;
  int z;
  int ax, ay, ans;
  while (n--) {
    scanf("%d", &z);
    ans = inf;
    for (int i = 1; i <= k; i++)
      for (int j = 1; j <= k - z + 1; j++) {
        bool f = 1;
        for (int t = j; t < j + z; t++) {
          if (vis[i][t]) {
            f = 0;
            break;
          }
        }
        if (f) {
          int s = 0;
          for (int k = j; k < j + z; k++) s += abs(i - x) + abs(k - y);
          if (s < ans) {
            ans = s;
            ax = i;
            ay = j;
          }
        }
      }
    if (ans == inf)
      printf("-1\n");
    else {
      for (int i = ay; i < ay + z; i++) vis[ax][i] = 1;
      printf("%d %d %d\n", ax, ay, ay + z - 1, ans);
    }
  }
}
