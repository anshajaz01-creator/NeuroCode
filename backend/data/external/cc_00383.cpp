#include <bits/stdc++.h>
using namespace std;
int main() {
  std::ios::sync_with_stdio(false);
  int n, a;
  long long ans = 0;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a;
    ans += i * 1LL * (a - 1) + 1;
  }
  cout << ans << "\n";
  return 0;
}
