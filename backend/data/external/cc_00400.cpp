#include <bits/stdc++.h>
using namespace std;
long long sum_all_to_n(long long n, long long k) {
  return (n * (n - 1) / 2) - (k * (k - 1) / 2) + k;
}
int main() {
  long long n, k;
  cin >> n >> k;
  if (sum_all_to_n(k, 1) < n) {
    cout << -1 << endl;
  } else if (n == 1) {
    cout << 0 << endl;
  } else {
    long long start = 2, end = k;
    long long mid = end + (start - end) / 2;
    while (start < end) {
      if (sum_all_to_n(k, mid) >= n) {
        start = mid;
      } else {
        end = mid - 1;
      }
      mid = start + (end - start + 1) / 2;
    }
    cout << k - mid + 1 << endl;
  }
  return 0;
}
