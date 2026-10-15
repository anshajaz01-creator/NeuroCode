#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  int a[100001];
  int b[100000];
  int p = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    p += (a[i] / 10);
  }
  for (int i = 0; i < n; i++) {
    float m = a[i];
    m = ceil(m / 10);
    b[i] = (m * 10 - a[i]);
  }
  sort(b, b + n);
  int sum = 0;
  int j = 0;
  int k1 = k;
  int j1 = 0;
  while (sum < k && j1 < n) {
    if (sum + b[j1] <= k) {
      sum += b[j1];
      k1 -= b[j1];
      if (b[j1] != 0) j++;
      j1++;
    } else {
      break;
    }
  }
  k1 /= 10;
  if (k1 < 0) k1 = 0;
  if (j + k1 + p > n * 10) {
    sum = n * 10;
  } else {
    sum = j + k1 + p;
  }
  printf("%d", sum);
  return 0;
}
