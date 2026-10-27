#include <bits/stdc++.h>
using namespace std;
int MOD = 1000000007;
int dp[701][701][3][3];
int ma[701];
int sta[701];
int topInd;
string str;
long long solve(int l, int r, int cl, int cr) {
  if (l >= r) return cl == 0 && cr == 0 ? 1 : 0;
  if (dp[l][r][cl][cr] != -1) {
    return dp[l][r][cl][cr];
  }
  long long res = 0;
  if (ma[l] == r) {
    if (!((cl == 0) ^ (cr == 0))) return dp[l][r][cl][cr] = 0;
    for (int ncl = 0; ncl < 3; ncl++) {
      for (int ncr = 0; ncr < 3; ncr++) {
        if (cl != 0 && ncl != 0 && cl == ncl) continue;
        if (cr != 0 && ncr != 0 && cr == ncr) continue;
        res = (res + solve(l + 1, r - 1, ncl, ncr)) % MOD;
      }
    }
  } else {
    for (int c1 = 0; c1 < 3; c1++) {
      for (int c2 = 0; c2 < 3; c2++) {
        if (c1 == 0 || c2 == 0 || c1 != c2)
          res = (res + solve(l, ma[l], cl, c1) * solve(ma[l] + 1, r, c2, cr)) %
                MOD;
      }
    }
  }
  return dp[l][r][cl][cr] = res;
}
int main() {
  memset(dp, -1, sizeof(dp));
  cin >> str;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '(') {
      sta[topInd++] = i;
    } else {
      ma[i] = sta[topInd - 1];
      ma[sta[topInd - 1]] = i;
      topInd--;
    }
  }
  long long ans = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ans = (ans + (solve(0, str.size() - 1, i, j))) % MOD;
    }
  }
  cout << ans << endl;
  return 0;
}
