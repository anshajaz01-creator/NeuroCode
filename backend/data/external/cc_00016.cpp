#include <bits/stdc++.h>
using namespace std;
typedef struct bottle {
  int left, vol;
} bottle;
bottle b[105];
bool cmp(bottle a, bottle b) {
  if (a.vol != b.vol) return a.vol > b.vol;
  return a.left > b.left;
}
int main() {
  int n;
  cin >> n;
  int dp[105][10005];
  int sum = 0;
  memset(dp, -1, sizeof(dp));
  for (int i = 1; i <= n; ++i) {
    cin >> b[i].left;
    sum += b[i].left;
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i].vol;
  }
  int cnt = 0;
  int total = 0;
  sort(b + 1, b + n + 1, cmp);
  for (int i = 1; i <= n; ++i) {
    total += b[i].vol;
    if (total >= sum) {
      cnt = i;
      break;
    }
  }
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = sum; (j - b[i].left) >= 0; --j) {
      for (int k = i; k >= 1; --k) {
        if (dp[k - 1][j - b[i].left] != -1)
          dp[k][j] = max(dp[k][j], dp[k - 1][j - b[i].left] + b[i].vol);
      }
    }
  }
  int ans = 0;
  for (int i = sum; i >= 1; --i) {
    if (dp[cnt][i] >= sum) {
      ans = sum - i;
      break;
    }
  }
  cout << cnt << " " << ans;
  return 0;
}
