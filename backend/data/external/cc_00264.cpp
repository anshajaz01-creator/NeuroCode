#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
const int mx = 5005;
long long a[mx], I[mx];
double b[mx];
long long dp[mx];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long t, i, j, cas = 0;
  long long n, m;
  cin >> n >> m;
  for (i = 0; i < n; i++) cin >> a[i] >> b[i];
  long long lis = 0;
  dp[0] = 1;
  for (i = 1; i < n; i++) {
    dp[i] = 1;
    for (j = 0; j < i; j++) {
      if (a[j] <= a[i]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }
  for (i = 0; i < n; i++) lis = max(lis, dp[i]);
  cout << n - lis << endl;
  return 0;
}
