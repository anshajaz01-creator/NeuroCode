#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, m;
  long long odd1, even1, odd2, even2;
  while (cin >> n >> m) {
    odd1 = 0;
    even1 = 0;
    long long x, y;
    for (int i = 0; i < n; i++) {
      cin >> x;
      if (x % 2 == 0) {
        even1++;
      } else
        odd1++;
    }
    odd2 = 0;
    even2 = 0;
    for (int i = 0; i < m; i++) {
      cin >> y;
      if (y % 2 == 0) {
        even2++;
      } else
        odd2++;
    }
    long long mn1;
    long long mn2;
    mn1 = min(odd1, even2);
    mn2 = min(odd2, even1);
    cout << mn1 + mn2 << endl;
  }
  return 0;
}
