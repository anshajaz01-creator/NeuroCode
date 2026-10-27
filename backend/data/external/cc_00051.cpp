#include <bits/stdc++.h>
using namespace std;
long long ans;
int n, s, a[200005], i;
int main() {
  cin >> n >> s;
  for (i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  sort(a, a + n);
  ans = 0;
  if (a[n / 2] == s) {
    cout << 0 << endl;
    return 0;
  } else if (a[n / 2] < s) {
    for (i = n / 2; i < n; i++) ans += (long long)max(0, s - a[i]);
  } else {
    for (i = 0; i <= n / 2; i++) ans += (long long)max(0, a[i] - s);
  }
  cout << ans << endl;
}
