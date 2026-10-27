#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int ts = 1;
  while (ts--) {
    long long n, m, k;
    cin >> n >> m >> k;
    long long a[m];
    for (int i = int(0); i < int(m); i++) cin >> a[i];
    long long s, e;
    if (a[0] % k) {
      s = (a[0] / k) * k + 1;
      e = s + k - 1;
    } else {
      e = a[0];
      s = a[0] - k + 1;
    }
    long long i = 0, sum = 0;
    while (i < m) {
      long long c = 0;
      while (i < m && a[i] >= s && a[i] <= e) c++, i++;
      if (c) {
        e += c;
        sum++;
      } else {
        if ((a[i] - e) % k) {
          s = (a[i] - e) / k;
          s = s * k + e + 1;
          e = s + k - 1;
        } else {
          e = a[i];
          s = e - k + 1;
        }
      }
    }
    cout << sum << "\n";
  }
  return 0;
}
