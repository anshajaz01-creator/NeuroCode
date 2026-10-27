#include <bits/stdc++.h>
using namespace std;
int main() {
  unsigned long long int n, c, sa, ma, a;
  cin >> sa >> ma >> a;
  n = sa % a, c = ma % a;
  if (n == 0 && c == 0) {
    cout << (sa / a) + (ma / a) << " " << 0;
  } else {
    if (n + c >= a) {
      unsigned long long int t1, t2, x;
      t1 = max(n, c);
      t2 = min(n, c);
      x = a - t1;
      cout << (sa / a) + (ma / a) + 1 << " " << x;
    } else
      cout << (sa / a) + (ma / a) << " " << 0;
  }
  return 0;
}
