#include <bits/stdc++.h>
using namespace std;
long long n;
long long a[400000];
int32_t main() {
  long long t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (long long i = 0; i < n; i++) cin >> a[i];
    if (n < 5) {
      cout << "0 0 0\n";
      continue;
    }
    long long lim = n / 2;
    long long i = 0;
    while (i < lim - 1 && a[i] == a[i + 1]) i++;
    long long g = i + 1;
    long long s = i + 2;
    long long b = i + 2;
    if (g + s + b > lim) {
      cout << "0 0 0\n";
      continue;
    }
    i += s;
    while (i < lim - 1 && a[i] == a[i + 1]) i++, s++;
    i += b;
    while (i < lim - 1) i++, b++;
    if (a[i] == a[i + 1]) {
      while (i >= 0 && a[i + 1] == a[i]) i--, b--;
    }
    if (g < s && g < b && s + g + b <= lim)
      cout << g << " " << s << " " << b << "\n";
    else
      cout << "0 0 0\n";
  }
}
