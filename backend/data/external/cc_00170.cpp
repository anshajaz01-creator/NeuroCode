#include <bits/stdc++.h>
int n, m, k, cx, cx1, visit[501][501], di[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
char a[501][501];
void print_num() {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (a[i][j] == '.' && visit[i][j] == 0) a[i][j] = 'X';
    }
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("%c", a[i][j]);
    }
    printf("\n");
  }
}
void dfs(int x, int y) {
  visit[x][y] = 1;
  cx1++;
  if (cx1 == cx - k) {
    print_num();
    return;
  }
  int i = 0, j, k1;
  while (i < 4) {
    j = x + di[i][0];
    k1 = y + di[i][1];
    if (j < n && j >= 0 && k1 < m && k1 >= 0 && a[j][k1] == '.' &&
        visit[j][k1] == 0)
      dfs(j, k1);
    i++;
  }
}
int main() {
  while (~scanf("%d%d%d", &n, &m, &k)) {
    int i, j, zx, zy;
    cx1 = cx = 0;
    memset(a, 0, sizeof(a));
    memset(visit, 0, sizeof(visit));
    for (i = 0; i < n; i++) {
      scanf("%s", a[i]);
      for (j = 0; j < m; j++) {
        if (a[i][j] == '.') {
          cx++;
          zx = i;
          zy = j;
        }
      }
    }
    dfs(zx, zy);
  }
  return 0;
}
