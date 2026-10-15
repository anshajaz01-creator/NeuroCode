#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;
long long int power(long long int x, long long int y, long long int p) {
  long long int temp;
  if (y <= 0) return 1;
  temp = power(x, y / 2, p);
  if (y % 2 == 0) {
    return (temp * temp) % p;
  } else {
    return (((x * temp) % p) * temp) % p;
  }
}
long long int modInverse(long long int n, long long int p) {
  return power(n, p - 2, p);
}
long long int nCrModPFermat(long long int n, long long int r, long long int p) {
  if (r == 0) {
    return 1;
  }
  long long int fac[n + 1];
  fac[0] = 1;
  for (long long int i = 1; i <= n; i++) {
    fac[i] = fac[i - 1] * i % p;
  }
  return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) %
         p;
}
void leftRotatebyOne(long long int arr[], int n) {
  int temp = arr[0], i;
  for (i = 0; i < n - 1; i++) arr[i] = arr[i + 1];
  arr[i] = temp;
}
void leftRotate(long long int arr[], int d, int n) {
  for (int i = 0; i < d; i++) leftRotatebyOne(arr, n);
}
int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  long long int t;
  cin >> t;
  for (long long int j = 0; j < t; j++) {
    long long int n, x, m;
    cin >> n >> x >> m;
    long long int left = x;
    long long int right = x;
    while (m--) {
      long long int l, r;
      cin >> l >> r;
      if (!(l > right || r < left)) {
        left = min(left, l);
        right = max(right, r);
      }
    }
    cout << right - left + 1 << endl;
  }
  return 0;
}
