#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m, a[105], b[105];
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d%d", &a[i], &b[i]);
  int dis = 0;
  for (int i = 0; i < n; i++)
    if (a[i] <= dis)
      if (b[i] > dis) dis = b[i];
  if (dis >= m)
    printf("YES\n");
  else
    printf("NO\n");
}
