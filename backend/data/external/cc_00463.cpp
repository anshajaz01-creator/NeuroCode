#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  int a[n];
  int b[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  int diff[n];
  for (int i = 0; i < n; i++) {
    diff[i] = a[i] - k * b[i];
  }
  int bound = 300005;
  int ans[bound];
  memset(ans, -1, sizeof(ans));
  ans[150000] = 0;
  for (int i = 0; i < n; i++) {
    int cur = diff[i];
    if (cur < 0) {
      for (int j = 0; j < bound; j++) {
        if (ans[j] != -1) {
          ans[j + cur] = max(ans[j + cur], ans[j] + a[i]);
        }
      }
    } else {
      for (int j = bound - 1; j >= 0; j--) {
        if (ans[j] != -1) {
          ans[j + cur] = max(ans[j + cur], ans[j] + a[i]);
        }
      }
    }
  }
  if (ans[150000] == 0) {
    cout << -1;
  } else {
    cout << ans[150000];
  }
  return 0;
}
