#include <bits/stdc++.h>
using namespace std;
int n, a[100010], b[100010];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    b[i] = a[i];
  }
  sort(b + 1, b + n + 1);
  int cont = 0;
  for (int i = 1; i <= n; ++i) {
    if (b[i] != a[i]) {
      cont++;
    }
  }
  if (cont == 2 || cont == 0) {
    printf("YES");
  } else {
    printf("NO");
  }
  return 0;
}
