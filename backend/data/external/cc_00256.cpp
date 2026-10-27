#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
char s[707];
int n, f[707][707][3][3], par[707];
void inc(int &x, int val) {
  x += val;
  if (x >= mod) x -= mod;
}
int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++)
    if (!par[i]) {
      int cnt = 1;
      for (int j = i + 1; j <= n; j++) {
        if (s[j] == '(')
          cnt++;
        else
          cnt--;
        if (!cnt) {
          par[i] = j, par[j] = i;
          break;
        }
      }
    }
  for (int d = 2; d <= n; d += 2) {
    for (int i = 1; i <= n - d + 1; i++) {
      int j = i + d - 1;
      int k = par[i];
      if (k < i || k > j) continue;
      if (k == j) {
        if (j == i + 1)
          f[i][j][0][1] = f[i][j][1][0] = f[i][j][0][2] = f[i][j][2][0] = 1;
        else {
          for (int x = 0; x <= 2; x++) {
            for (int y = 0; y <= 2; y++)
              if (!x + !y == 1) {
                for (int xx = 0; xx <= 2; xx++) {
                  for (int yy = 0; yy <= 2; yy++) {
                    if (x && x == xx || y && y == yy) continue;
                    inc(f[i][j][x][y], f[i + 1][j - 1][xx][yy]);
                  }
                }
              }
          }
        }
      } else {
        for (int x = 0; x <= 2; x++) {
          for (int y = 0; y <= 2; y++)
            if (!x + !y == 1) {
              for (int xx = 0; xx <= 2; xx++) {
                for (int yy = 0; yy <= 2; yy++) {
                  if (y != xx || !y)
                    inc(f[i][j][x][yy],
                        1ll * f[i][k][x][y] * f[k + 1][j][xx][yy] % mod);
                }
              }
            }
        }
      }
    }
  }
  int ans = 0;
  for (int x = 0; x <= 2; x++)
    for (int y = 0; y <= 2; y++) inc(ans, f[1][n][x][y]);
  printf("%d\n", ans);
  return 0;
}
