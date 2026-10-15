#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n;
  cin >> n;
  int a[n], g[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> g[i];
  }
  long long int asum = 0, gsum = 0;
  if (n == 0) return 0;
  string s;
  for (int i = 0; i < n; i++) {
    if (asum + a[i] - gsum >= 500) {
      gsum += g[i];
      s.push_back('G');
    } else {
      s.push_back('A');
      asum += a[i];
    }
  }
  if (abs(gsum - asum) <= 500 && s.size() == n) {
    cout << s;
  } else {
    cout << -1;
  }
  return 0;
}
