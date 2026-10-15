#include <bits/stdc++.h>
using namespace std;
int main() {
  unsigned int n, k;
  cin >> n >> k;
  int a[n];
  int b[n];
  unsigned int sum = 0;
  unsigned int sum2 = 0;
  for (int i = 0; i <= n - 1; i++) {
    cin >> a[i];
    sum2 += a[i];
    sum += a[i] / 10;
    b[i] = a[i] % 10;
  }
  sort(b, b + n);
  unsigned int h = 100 * n - sum2;
  k = k > h ? h : k;
  for (int i = n - 1; i >= 0; i--) {
    if (k > 0 && k >= (10 - b[i])) {
      k = k + b[i] - 10;
      sum++;
    } else {
      break;
    }
  }
  if (k > 0) sum += k / 10;
  cout << sum;
  return 0;
}
