#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 52;
const long long MOD = 1000000007;
long long dp[MAX_N][MAX_N][MAX_N][MAX_N];
int n, p;
int color[MAX_N];
long long pw[MAX_N];
long long C[MAX_N][MAX_N];
long long odd[MAX_N], even[MAX_N];
void init() {
  pw[0] = 1LL;
  for (int i = 1; i <= n; i++) {
    pw[i] = (pw[i - 1] * 2LL) % MOD;
  }
  for (int i = 0; i <= n; i++) {
    C[i][0] = 1LL;
    C[i][i] = 1LL;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j += 2) {
      (even[i] += C[i][j]) %= MOD;
    }
    for (int j = 1; j <= i; j += 2) {
      (odd[i] += C[i][j]) %= MOD;
    }
  }
}
void update(int ew, int ow, int eb, int ob, int c, long long v) {
  if (c != 1) {
    (dp[ew + 1][ow][eb][ob] +=
     ((v * odd[ob]) % MOD * pw[ew + ow + eb]) % MOD) %= MOD;
    (dp[ew][ow + 1][eb][ob] +=
     ((v * even[ob]) % MOD * pw[ew + ow + eb]) % MOD) %= MOD;
  }
  if (c != 0) {
    (dp[ew][ow][eb + 1][ob] +=
     ((v * odd[ow]) % MOD * pw[eb + ob + ew]) % MOD) %= MOD;
    (dp[ew][ow][eb][ob + 1] +=
     ((v * even[ow]) % MOD * pw[eb + ob + ew]) % MOD) %= MOD;
  }
}
int main() {
  cin >> n >> p;
  init();
  for (int i = 1; i <= n; i++) {
    cin >> color[i];
  }
  dp[0][0][0][0] = 1LL;
  long long ans = 0LL;
  for (int i = 0; i <= n; i++) {
    for (int ew = 0; ew <= i; ew++) {
      for (int ow = 0; ow + ew <= i; ow++) {
        for (int eb = 0; eb + ew + ow <= i; eb++) {
          int ob = i - ew - ow - eb;
          if (dp[ew][ow][eb][ob] == 0) {
            continue;
          }
          long long cur = dp[ew][ow][eb][ob];
          if (i == n && ((ow + ob) % 2 == p)) {
            (ans += dp[ew][ow][eb][ob]) %= MOD;
          }
          update(ew, ow, eb, ob, color[i + 1], cur);
        }
      }
    }
  }
  cout << ans;
  return 0;
}
