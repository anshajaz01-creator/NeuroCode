#include <bits/stdc++.h>
using namespace std;
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long int n, k;
  cin >> n >> k;
  long long int a[n];
  for (long long int i = 0; i < n; i++) {
    cin >> a[i];
  }
  long long int remain = 0;
  long long int ans = 0, prev;
  for (long long int i = 0; i < n; i++) {
    prev = ans;
    ans += (a[i] + remain) / k;
    if (i != n - 1 && (ans - prev) * k < remain) {
      ans++;
      remain = 0;
    } else if ((ans - prev) * k < remain) {
      remain = remain + a[i];
    } else
      remain = -(ans - prev) * k + (a[i] + remain);
  }
  prev = ans;
  ans += (remain) / k;
  if (ans == prev && remain != 0) ans++;
  cout << ans << endl;
}
