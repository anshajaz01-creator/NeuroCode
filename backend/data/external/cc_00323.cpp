#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n;
  cin >> n;
  string a;
  cin >> a;
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
  for (long long i = 0; i < n; i++) {
    if (i % 2 == 0 && a[i] != 'r') c1++;
    if (i % 2 == 1 && a[i] != 'b') c2++;
  }
  for (long long i = 0; i < n; i++) {
    if (i % 2 == 0 && a[i] != 'b') c3++;
    if (i % 2 == 1 && a[i] != 'r') c4++;
  }
  cout << min(max(c1, c2), max(c3, c4));
}
