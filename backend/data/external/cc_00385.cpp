#include <bits/stdc++.h>
using namespace std;
int main() {
  unsigned long long n, a[100], c;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    c = (i == 0 ? a[i] : c + 1 + (a[i] - 1) * (i + 1));
  }
  cout << c << endl;
  return 0;
}
