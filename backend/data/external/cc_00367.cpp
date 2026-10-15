#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++) cin >> a[i];
  int t = 0;
  for (int i = 0; i < 17; i++) {
    if ((1 + (int)pow(2, i)) > n)
      break;
    else
      t = i;
  }
  int x = (int)pow(2, t);
  int y = t;
  int sum = 0;
  for (int i = 0; i < n - 1; i++) {
    if (i + x >= n) {
      y--;
      x = (int)pow(2, y);
    }
    sum += a[i];
    cout << sum << endl;
    a[i + x] += a[i];
  }
  return 0;
}
