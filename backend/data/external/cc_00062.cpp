#include <bits/stdc++.h>
using namespace std;
const int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int n, b, Q, cpos[2][4016100], v[100010];
long long t[100010];
class node {
 public:
  int x, y, d;
  node() {}
  node(int tx, int ty, int td) { x = tx, y = ty, d = td; }
  inline int id() { return (x * (b + 1) + y) * 4 + d; }
  inline node mov(int k) {
    int nx = (x + dir[k][0]), ny = (y + dir[k][1]);
    nx = min(max(nx, 0), b);
    ny = min(max(ny, 0), b);
    return node(nx, ny, k);
  }
} p[4016100];
int ti, tj;
char tk;
int main() {
  scanf("%d%d", &n, &b);
  for (int i = 0; i <= b; i++) {
    for (int j = 0; j <= b; j++) {
      for (int k = 0; k < 4; k++) {
        p[node(i, j, k).id()] = node(i, j, k).mov(k);
      }
    }
  }
  for (int i = 1, stx, sty, edx, edy; i <= n; i++) {
    scanf("%d%d%d%d", &stx, &sty, &edx, &edy);
    int len = abs(edx - stx) + abs(edy - sty);
    for (int j = 0; j < 4; j++) {
      if (edx == stx + dir[j][0] * len && edy == sty + dir[j][1] * len) {
        int curx = stx, cury = sty;
        for (int k = 0; k <= len; k++) {
          for (int l = 0; l < 4; l++)
            p[node(curx, cury, l).id()] = p[node(curx, cury, j).id()];
          curx += dir[j][0];
          cury += dir[j][1];
        }
        break;
      }
    }
  }
  scanf("%d", &Q);
  for (int i = 1; i <= Q; i++) {
    scanf("%d %d %c %lld", &ti, &tj, &tk, &t[i]);
    if (tk == 'U')
      tk = 0;
    else if (tk == 'D')
      tk = 1;
    else if (tk == 'L')
      tk = 2;
    else
      tk = 3;
    v[i] = node(ti, tj, tk).id();
  }
  int tot = 4 * (b + 1) * (b + 1);
  for (int i = 0; i < tot; i++) cpos[0][i] = p[i].id();
  for (int i = 0; i < 50; i++) {
    for (int j = 1; j <= Q; j++)
      if ((t[j] >> i) & 1) v[j] = cpos[0][v[j]];
    for (int j = 0; j < tot; j++) cpos[1][j] = cpos[0][cpos[0][j]];
    memcpy(cpos[0], cpos[1], sizeof(cpos[0]));
  }
  for (int i = 1; i <= Q; i++)
    printf("%d %d\n", v[i] / 4 / (b + 1), (v[i] / 4) % (b + 1));
  return 0;
}
