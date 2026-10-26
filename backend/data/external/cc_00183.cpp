#include <bits/stdc++.h>
using namespace std;
long long a[500001];
long long b[500001];
long long sum[500001];
long long dpUp[500001];
long long dpDown[500001];
int main() {
  int n;
  long long maximum = 0;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }
  for (int i = n; i >= 1; --i) {
    sum[i] = sum[i + 1] + a[i] + b[i];
    dpUp[i] = dpUp[i + 1] + sum[i + 1] + (2 * (n - i) + 1) * b[i];
    dpDown[i] = dpDown[i + 1] + sum[i + 1] + (2 * (n - i) + 1) * a[i];
  }
  maximum = dpUp[1];
  long long soFar = 0;
  for (int i = 1; i <= n; ++i) {
    if (i % 2) {
      soFar += (i - 1) * 2 * a[i];
      soFar += ((i - 1) * 2 + 1) * b[i];
      maximum = max(maximum, soFar + sum[i + 1] * 2 * i + dpDown[i + 1]);
    } else {
      soFar += (i - 1) * 2 * b[i];
      soFar += ((i - 1) * 2 + 1) * a[i];
      maximum = max(maximum, soFar + sum[i + 1] * 2 * i + dpUp[i + 1]);
    }
  }
  cout << maximum;
  return 0;
}
