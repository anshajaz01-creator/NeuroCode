#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e5 + 100;
int n, k;
int a[MAX_N];
int cnt[MAX_N];
int cost[MAX_N];
int has[MAX_N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> k;
  memset(cnt, 0, sizeof cnt);
  memset(cost, 0, sizeof cost);
  memset(has, 0, sizeof has);
  bool ok = false;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    cnt[a[i]]++;
    if (cnt[a[i]] >= k) {
      ok = true;
    }
  }
  if (ok) {
    cout << "0" << endl;
    return 0;
  }
  sort(a + 1, a + 1 + n);
  int ans = 1e9;
  while (1) {
    bool can = false;
    for (int i = 1; i <= n; ++i) {
      if (a[i] != -1) {
        can = true;
        a[i] >>= 1;
        has[i]++;
        cnt[a[i]]++;
        cost[a[i]] += has[i];
        if (cnt[a[i]] >= k) {
          ans = min(cost[a[i]], ans);
        }
        if (a[i] == 0) a[i] = -1;
      }
    }
    if (!can) break;
  }
  cout << ans << endl;
  return 0;
}
