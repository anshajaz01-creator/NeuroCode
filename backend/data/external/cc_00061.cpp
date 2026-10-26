#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const double eps = 1e-9;
const double INF = inf;
const double EPS = eps;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int N[2][1100 * 1100 * 4];
long long T[110000];
int V[110000];
int main() {
  int x, y, n, q, a, b, c, d, bb, it;
  int i, j, k, nx, ny;
  char ch;
  scanf("%d%d", &n, &b);
  for (i = 0; i <= b; i++)
    for (j = 0; j <= b; j++)
      for (k = 0; k < 4; k++) {
        nx = i + dx[k], ny = j + dy[k];
        nx = max(nx, 0), nx = min(nx, b);
        ny = max(ny, 0), ny = min(ny, b);
        N[0][(i * (b + 1) + j) * 4 + k] = (nx * (b + 1) + ny) * 4 + k;
      }
  for (i = 0; i < n; i++) {
    scanf("%d%d%d%d", &a, &bb, &c, &d);
    assert(a != c || bb != d);
    int len = abs(a - c) + abs(bb - d);
    for (it = 0; it < 4; it++)
      if (c == a + len * dx[it] && d == bb + len * dy[it]) {
        for (j = 0; j <= len; j++) {
          x = a + j * dx[it], y = bb + j * dy[it];
          int id = (x * (b + 1) + y) * 4;
          for (k = 0; k < 4; k++) {
            N[0][id + k] = N[0][id + it];
          }
        }
        break;
      }
  }
  scanf("%d", &q);
  for (i = 0; i < q; i++) {
    scanf("%d%d %c %I64d", &x, &y, &ch, &T[i]);
    V[i] = (x * (b + 1) + y) * 4;
    if (ch == 'L') V[i]++;
    if (ch == 'U') V[i] += 2;
    if (ch == 'D') V[i] += 3;
  }
  for (it = 0; it < 55; it++) {
    for (i = 0; i < q; i++)
      if (T[i] & (1ll << it)) V[i] = N[0][V[i]];
    for (j = 0; j < (b + 1) * (b + 1) * 4; j++) N[1][j] = N[0][N[0][j]];
    memcpy(N[0], N[1], sizeof(N[0]));
  }
  for (i = 0; i < q; i++)
    printf("%d %d\n", V[i] / (4 * (b + 1)), (V[i] / 4) % (b + 1));
  ;
  return 0;
}
