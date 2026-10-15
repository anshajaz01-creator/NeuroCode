#include <bits/stdc++.h>
using namespace std;
const int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
char s[505][505];
void dfs(int x, int y, int &k, int n, int m) {
  if (!k) return;
  s[x][y] = '.';
  k--;
  for (int i = 0; i < 4; i++) {
    int tx = x + d[i][0];
    int ty = y + d[i][1];
    if (tx >= 0 && tx < n && ty >= 0 && ty < m && s[tx][ty] == 'X')
      dfs(tx, ty, k, n, m);
  }
}
int main() {
  int n, m, k, cnt = 0;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; i++) scanf("%s", s[i]);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (s[i][j] == '.') {
        s[i][j] = 'X';
        cnt++;
      }
    }
  k = cnt - k;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (s[i][j] == 'X') dfs(i, j, k, n, m);
  for (int i = 0; i < n; i++) printf("%s\n", s[i]);
  return 0;
}
