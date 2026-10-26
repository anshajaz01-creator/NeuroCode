#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, aa, bb;
  cin >> n >> aa >> bb;
  int a[n], sum = 0;
  vector<int> v;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sum += a[i];
    if (i >= 1) {
      v.push_back(a[i]);
    }
  }
  sort(v.begin(), v.end());
  double litre = (a[0] * aa * 1.0) / (sum * 1.0);
  int hole = 0, i = n - 2;
  while (litre < bb) {
    hole++;
    sum -= v[i];
    i--;
    litre = (a[0] * aa * 1.0) / (sum * 1.0);
  }
  cout << hole;
}
