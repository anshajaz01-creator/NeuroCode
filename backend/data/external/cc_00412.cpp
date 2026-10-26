#include <bits/stdc++.h>
using namespace std;
int n, k, a[1010], ans;
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  sort(a, a + n);
  ans = 0;
  for (int i = 0; i < n; i++) {
    while (k * 2 < a[i]) {
      k <<= 1;
      ans++;
    }
    k = max(k, a[i]);
  }
  printf("%d\n", ans);
  return 0;
}
