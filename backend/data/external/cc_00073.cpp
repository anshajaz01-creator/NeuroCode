#include <bits/stdc++.h>
int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }
int main() {
  char a[100010];
  int x, count = 0, z = 0, j, i, n, b[100010], l = 0;
  scanf("%s", a);
  n = strlen(a);
  for (i = n - 1; a[i] != '#' && z >= 0 && i >= 0; i--)
    if (a[i] == '(')
      z--;
    else
      z++;
  if (z < 0)
    printf("-1\n");
  else {
    x = z;
    z = 0;
    l = 0;
    for (j = 0; j < i; j++) {
      if (a[j] == '(')
        z++;
      else if (a[j] == ')')
        z--;
      else {
        b[l++] = z;
        z = 0;
      }
    }
    count = 0;
    b[l++] = z - x;
    for (i = 0; i < l; i++)
      if (b[i] <= 0) {
        count += 1 - b[i];
        b[i] = 1;
      }
    for (i = 0; i < l; i++)
      if (b[i] > 0) {
        if (b[i] - 1 >= count) {
          b[i] -= count;
          count = 0;
        } else {
          count = count - b[i] + 1;
          b[i] = 1;
        }
      }
    if (count > 0)
      printf("-1\n");
    else {
      x = 0;
      z = 0;
      qsort(b, l, sizeof(int), cmp);
      for (i = 0; i < n && z <= 0; i++) {
        if (a[i] == '(')
          z--;
        else if (a[i] == ')')
          z++;
        else
          z += b[x++];
      }
      if (i == n) {
        for (i = 0; i < l; i++) printf("%d\n", b[i]);
      } else
        printf("-1\n");
    }
  }
  return 0;
}
