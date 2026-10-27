#include <bits/stdc++.h>
using namespace std;
long long sum, a, i, b;
int main() {
  cin >> a;
  for (i = 1; i <= a; i++) {
    cin >> b;
    if (i == 1)
      sum = b;
    else
      sum += i * (b - 1) + 1;
  }
  cout << sum;
  return 0;
}
