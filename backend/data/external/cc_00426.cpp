#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  while (cin >> n) {
    int a, sum = 0;
    for (int i = 0; i < n; i++) cin >> a, sum += a;
    if (sum % n == 0)
      cout << n << endl;
    else
      cout << n - 1 << endl;
  }
}
