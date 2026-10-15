#include <bits/stdc++.h>
using namespace std;
long long ans, n;
int main() {
  cin >> n;
  for (int i = 2; i <= n; i++)
    for (int j = 2 * i; j <= n; j += i) ans += 4 * (j / i);
  cout << ans;
  return 0;
}
