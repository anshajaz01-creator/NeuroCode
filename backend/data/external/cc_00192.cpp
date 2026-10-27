#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m, b, sum = 0, q, even = 0, odd = 0;
  cin >> n >> m;
  int arr[n];
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    if (arr[i] % 2 == 0)
      even++;
    else
      odd++;
  }
  for (int i = 0; i < m; ++i) {
    cin >> b;
    if (b % 2 == 0) {
      if (odd == 0)
        continue;
      else {
        odd--;
        sum++;
      }
    }
    if (b % 2 != 0) {
      if (even == 0)
        continue;
      else {
        even--;
        sum++;
      }
    }
  }
  cout << sum;
}
