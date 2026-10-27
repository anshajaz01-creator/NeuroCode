#include <bits/stdc++.h>
using namespace std;
const int maxx = 2e5 + 10;
long long ans = 1e18;
int a[maxx];
int num[maxx], cnt[maxx];
long long ad[maxx], re[maxx], le[maxx], mo[maxx];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  int e = 0, k = 0;
  for (int i = 0; i < n; i++) {
    e++;
    if (a[i] != a[i + 1]) {
      num[k] = a[i];
      cnt[k++] = e;
      e = 0;
    }
  }
  for (int i = 1; i < k; i++) {
    int M = num[i] - num[i - 1];
    ad[i] = ad[i - 1] + le[i - 1] * M + cnt[i - 1] * (M - 1);
    le[i] = le[i - 1] + cnt[i - 1];
  }
  for (int i = k - 2; i >= 0; i--) {
    int M = num[i + 1] - num[i];
    re[i] = re[i + 1] + mo[i + 1] * M + cnt[i + 1] * (M - 1);
    mo[i] = mo[i + 1] + cnt[i + 1];
  }
  for (int i = 0; i < k; i++) {
    if (cnt[i] >= m) {
      cout << 0 << endl;
      return 0;
    }
    int cha = m - cnt[i];
    if (i > 0 && i < k - 1) ans = min(ans, ad[i] + re[i] + cha);
    if (i > 0 && le[i] >= cha) ans = min(ans, ad[i] + cha);
    if (i < k - 1 && mo[i] >= cha) ans = min(ans, re[i] + cha);
  }
  cout << ans << endl;
  return 0;
}
