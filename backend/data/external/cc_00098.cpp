#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  long long n, q, t, coins[35], temp[35], ans, c;
  memset(coins, 0, sizeof coins);
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    cin >> t;
    int val = 0;
    while (t % 2 == 0) val++, t /= 2;
    coins[val]++;
  }
  for (int i = 0; i < q; i++) {
    cin >> t;
    for (int j = 0; j < 35; j++) temp[j] = coins[j];
    ans = 0, c = 0;
    for (int j = 31; j >= 0; j--) {
      if (t & (1LL << j)) c += 1;
      int x = min(c, temp[j]);
      c -= x, ans += x;
      c *= 2;
    }
    if (c != 0)
      cout << -1 << endl;
    else
      cout << ans << endl;
  }
  return 0;
}
