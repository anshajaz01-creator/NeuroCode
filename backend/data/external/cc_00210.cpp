#include <bits/stdc++.h>
char s[500007][12];
int main() {
  int i, j, x, y, z, n, len[500007], mat[30][30];
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%s", s[i]);
    len[i] = strlen(s[i]);
  }
  memset(mat, -1, sizeof(mat));
  for (i = 0; i < n; i++) {
    x = s[i][0] - 'a';
    y = s[i][len[i] - 1] - 'a';
    for (j = 0; j < 26; j++)
      if (mat[j][x] != -1)
        mat[j][y] = ((mat[j][x] + len[i]) >= mat[j][y]) ? mat[j][x] + len[i]
                                                        : mat[j][y];
    mat[x][y] = (mat[x][y] >= len[i]) ? mat[x][y] : len[i];
  }
  z = 0;
  for (i = 0; i < 26; i++)
    for (j = 0; j < 26; j++)
      if (i == j) z = (z >= mat[i][j]) ? z : mat[i][j];
  printf("%d\n", z);
}
