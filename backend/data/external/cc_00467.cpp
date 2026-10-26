#include <bits/stdc++.h>
using namespace std;
unordered_map<
    long long,
    unordered_map<long long, pair<pair<long long, long long>, long long> > >
    inpmt;
vector<long long> dcp;
void SieveOfErat() {
  bool prime[1000001];
  memset(prime, true, sizeof(prime));
  for (long long vec = 2; vec * vec <= 1000000; vec++) {
    if (prime[vec] == true) {
      for (long long dd = vec * 2; dd <= 1000000; dd += vec) prime[dd] = false;
    }
  }
}
long long gcd(long long aa, long long id2) {
  if (aa == 0) {
    return id2;
  } else
    return gcd(aa % id2, id2);
}
struct vect {
  struct vect *foll;
  long long calc;
  struct vect *succ;
};
long long n, k;
long long a[200005];
long long b[200005];
long long dp[130][210000];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  memset(dp, -1000000010, sizeof(dp));
  dp[0][100000] = 0;
  for (long long i = 1; i <= n; i++) cin >> a[i];
  for (long long i = 1; i <= n; i++) cin >> b[i];
  for (long long i = 1; i <= n; i++) {
    for (long long j = k * b[i] - a[i]; j <= 200000; j++) {
      dp[i][j] = max(dp[i][j], dp[i - 1][j]);
      dp[i][j] = max(dp[i][j], dp[i - 1][j - k * b[i] + a[i]] + a[i]);
    }
  }
  if (dp[n][100000] == 0)
    cout << -1 << endl;
  else
    cout << dp[n][100000] << endl;
  return 0;
}
