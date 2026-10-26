#include <bits/stdc++.h>
using namespace std;
int n, m;
int a[5005], b[5005];
struct operation {
  int t, l, r, m;
} op[5005];
bool find() {
  int k;
  for (int i = 0; i < 5005; i++) a[i] = 1000000000;
  memset(b, 0, sizeof(b));
  for (int i = 1; i <= m; i++) {
    if (op[i].t == 1) {
      for (int p = op[i].l; p <= op[i].r; p++) b[p] += op[i].m;
    } else {
      for (int p = op[i].l; p <= op[i].r; p++) {
        a[p] = min(a[p], op[i].m - b[p]);
      }
    }
  }
  memset(b, 0, sizeof(b));
  for (int i = 1; i <= m; i++) {
    if (op[i].t == 1) {
      for (int p = op[i].l; p <= op[i].r; p++) b[p] += op[i].m;
    } else {
      k = -100000000;
      for (int p = op[i].l; p <= op[i].r; p++) {
        k = max(k, a[p] + b[p]);
      }
      if (k != op[i].m) return false;
    }
  }
  return true;
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d%d", &op[i].t, &op[i].l, &op[i].r, &op[i].m);
  }
  if (find()) {
    printf("YES\n");
    for (int i = 1; i <= n; i++) {
      printf("%d ", a[i]);
    }
  } else {
    printf("NO\n");
  }
  return 0;
}
