#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n, count = 0;
  double k;
  cin >> n >> k;
  long long int upper = 2 * k;
  long long int a[n];
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  for (int i = 0; i < n; i++) {
    if (upper >= a[i]) {
      upper = max(upper, 2 * a[i]);
    } else {
      while (upper < a[i]) {
        upper *= 2;
        count++;
      }
      upper = max(upper, 2 * a[i]);
    }
  }
  cout << count;
  return 0;
}
