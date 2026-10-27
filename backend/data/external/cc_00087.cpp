#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long t;
  cin >> t;
  while (t--) {
    long long n, i, g = 0, s = 0, b = 0, j;
    cin >> n;
    long long a[n];
    vector<long long> v(n, 1);
    for (i = 0; i < n; i++) {
      cin >> a[i];
    }
    if (n < 6)
      cout << "0 0 0\n";
    else {
      for (i = 0; i < n - 1; i++) {
        if (a[i] == a[i + 1]) v[i + 1] = v[i] + 1;
      }
      for (i = 0; i < n - 1; i++) {
        if (a[i] != a[i + 1]) {
          g = g + v[i];
          break;
        }
      }
      for (j = i + 1; j < n - 1; j++) {
        if (a[j] != a[j + 1] && j < n / 2) {
          s = s + v[j];
          if (s > g) {
            break;
          }
        }
      }
      for (long long l = j + 1; l < n - 1; l++) {
        if (l < n / 2 && a[l] != a[l + 1]) {
          b = b + v[l];
        }
      }
      if (g > 0 && s > 0 && b > 0 && g < s && g < b) {
        cout << g << " " << s << " " << b << "\n";
      } else
        cout << "0 0 0\n";
    }
  }
  return 0;
}
