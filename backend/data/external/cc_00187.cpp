#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  long long ans = 0;
  for (int i = 2; i <= n; i++) {
    for (int j = 2; j * j <= i; j++) {
      if (i % j == 0) {
        ans += ((i / j) * 4);
      }
      if (i % (i / j) == 0 && (i / j) != j) {
        ans += (j * 4);
      }
    }
  }
  cout << ans << endl;
  return 0;
}
