#include <bits/stdc++.h>
int main() {
  int n;
  double v;
  scanf("%d%lf", &n, &v);
  int a[10000];
  int i = 0;
  while (i < n) {
    scanf("%d", &a[i]);
    i++;
  }
  int b[10000];
  i = 0;
  while (i < n) {
    scanf("%d", &b[i]);
    i++;
  }
  i = 0;
  double min = b[0] * 1.00 / a[0] * 1.00;
  while (i < n) {
    if (min > b[i] * 1.00 / a[i] * 1.00) min = b[i] * 1.00 / a[i] * 1.00;
    if (min == 0.000) break;
    i++;
  }
  double sum = 0.00;
  i = 0;
  while (i < n) {
    sum = sum + min * a[i];
    i++;
  }
  if (sum <= v) {
    printf("%.4lf\n", sum);
  } else
    printf("%.4lf\n", v);
  return 0;
}
