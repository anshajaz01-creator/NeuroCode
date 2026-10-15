#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k;
  cin >> n >> k;
  vector<int> fav(1e5 + 5, 0), cnt(1e5 + 5, 0), incr(k + 3, 0);
  for (int i = 1; i <= k * n; i++) {
    int x;
    cin >> x;
    cnt[x]++;
  }
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    fav[x]++;
  }
  incr[0] = 0;
  for (int i = 1; i <= k; i++) {
    cin >> incr[i];
  }
  int ans = 0;
  for (int i = 1; i <= 100000; i++) {
    int dp[fav[i] + 3][cnt[i] + 3];
    for (int p = 0; p <= fav[i]; p++) {
      for (int q = 0; q <= cnt[i]; q++) {
        dp[p][q] = 0;
      }
    }
    for (int p = 1; p <= fav[i]; p++) {
      for (int q = 0; q <= cnt[i]; q++) {
        for (int r = 0; r <= k; r++) {
          if (q - r < 0) {
            continue;
          }
          dp[p][q] = max(dp[p][q], dp[p - 1][q - r] + incr[r]);
        }
      }
    }
    ans += dp[fav[i]][cnt[i]];
  }
  cout << ans;
  return 0;
}
