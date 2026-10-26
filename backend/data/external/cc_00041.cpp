#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n, i, r, p;
  cin >> r >> p;
  if (p - r >= 1) {
    cout << "2";
    return 0;
  } else if (r == p) {
    if (r % 2 == 0) {
      cout << "2";
      return 0;
    } else {
      cout << r;
      return 0;
    }
  }
}
