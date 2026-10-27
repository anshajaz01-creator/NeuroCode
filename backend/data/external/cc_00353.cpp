#include <bits/stdc++.h>
using namespace std;
int n, i, j, x, y, z, a[55][55], d[55][55][55][55];
char c;
int get(int f, int s, int l, int r) {
  return a[l][r] - a[l][s - 1] - a[f - 1][r] + a[f - 1][s - 1];
}
int main() {
  cin >> n;
  for (i = 1; i <= n; ++i)
    for (j = 1; j <= n; ++j) {
      cin >> c;
      a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
      if (c == '#') a[i][j]++;
    }
  for (i = n; i >= 1; --i)
    for (j = n; j >= 1; --j)
      for (x = i; x <= n; ++x)
        for (y = j; y <= n; ++y) {
          if (get(i, j, x, y) == 0) {
            d[i][j][x][y] = 0;
            continue;
          }
          d[i][j][x][y] = max(x - i + 1, y - j + 1);
          for (z = i; z <= x; ++z)
            if (get(z, j, z, y) == 0)
              d[i][j][x][y] =
                  min(d[i][j][z - 1][y] + d[z + 1][j][x][y], d[i][j][x][y]);
          for (z = j; z <= y; ++z)
            if (get(i, z, x, z) == 0)
              d[i][j][x][y] =
                  min(d[i][j][x][z - 1] + d[i][z + 1][x][y], d[i][j][x][y]);
        }
  cout << d[1][1][n][n];
}
