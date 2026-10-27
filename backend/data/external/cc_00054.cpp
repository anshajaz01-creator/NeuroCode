#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n, s;
  scanf("%lld", &n);
  scanf("%lld", &s);
  vector<long long int> v(n);
  for (long long int i = 0; i < n; ++i) {
    scanf("%lld", &v[i]);
  }
  if (n == 1) {
    cout << abs(v[0] - s);
    return 0;
  }
  sort(v.begin(), v.end());
  long long int x = n / 2;
  long long int m = v[x];
  if (s == m) {
    cout << 0;
    return 0;
  }
  long long int ans = 0;
  if (s < m) {
    long long int index = upper_bound(v.begin(), v.end(), s) - v.begin();
    for (long long int i = index; i <= x; ++i) {
      ans = ans + abs(v[i] - s);
    }
  } else {
    long long int index = upper_bound(v.begin(), v.end(), s) - v.begin() - 1;
    for (long long int i = x; i <= index; ++i) {
      ans += abs(v[i] - s);
    }
  }
  cout << ans;
  return 0;
}
