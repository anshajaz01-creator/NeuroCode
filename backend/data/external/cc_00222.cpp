#include <bits/stdc++.h>
using namespace std;
const long long maxn = 2e5 + 5;
long long n, V;
long double a[30], b[30], c[30], x = 101, sum;
int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> V;
  for (long long i = 0; i < n; i++) cin >> a[i];
  for (long long i = 0; i < n; i++) {
    cin >> b[i];
    c[i] = b[i] / a[i];
    x = min(x, c[i]);
    sum += a[i];
  }
  if (sum * x >= V)
    cout << V << endl;
  else
    cout << fixed << setprecision(5) << sum * x << endl;
}
