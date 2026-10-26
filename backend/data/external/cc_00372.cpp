#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
int n, a[N], neg, pos, zer;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    if (a[i] > 0) {
      pos++;
      printf("%d ", a[i]);
    } else if (a[i] < 0) {
      neg++;
    } else {
      zer++;
    }
  }
  if (n == 1 && a[1] < 0) {
    printf("%d", a[1]);
    return 0;
  }
  if (zer == n || zer == n - 1 && neg == 1) {
    printf("0");
    return 0;
  }
  sort(a + 1, a + n + 1);
  for (int j = 1; j <= neg / 2 * 2; j++) {
    printf("%d ", a[j]);
  }
  return 0;
}
