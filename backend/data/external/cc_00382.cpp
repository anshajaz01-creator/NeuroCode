#include <bits/stdc++.h>
const double pi = 4.0 * atan(1.0);
const double e = exp(1.0);
using namespace std;
long long n, m;
long long a[200005];
int main() {
  cin >> n >> m;
  long long s = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    s += a[i];
    cout << s / m << ' ';
    s -= s / m * m;
  }
}
