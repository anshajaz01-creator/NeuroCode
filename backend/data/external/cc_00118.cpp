#include <bits/stdc++.h>
using namespace std;
int a[100050];
void solve() {
  memset(a, 0, sizeof(a));
  int n, ans = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    if (a[i] != a[i - 1]) {
      ans++;
    }
  }
  cout << ans << endl;
}
int main() {
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}
