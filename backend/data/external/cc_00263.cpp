#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e9;
long long gcd(long long a, long long b) { return (a ? gcd(b % a, a) : b); }
long long power(long long a, long long n) {
  long long p = 1;
  while (n > 0) {
    if (n % 2) {
      p = p * a;
    }
    n >>= 1;
    a *= a;
  }
  return p;
}
int main() {
  ios_base::sync_with_stdio(false);
  int n, a[5010], dp[5010], m;
  memset(dp, 0, sizeof(dp));
  long double x;
  scanf("%d %d", &n, &m);
  for (int(i) = 1; (i) <= (n); (i)++) {
    scanf("%d %lf", a + i, &x);
  }
  for (int(i) = 1; (i) <= (n); (i)++) {
    for (int(j) = (a[i]); (j) >= (1); (j)--) {
      dp[a[i]] = (dp[a[i]] > dp[j] + 1 ? dp[a[i]] : dp[j] + 1);
    }
  }
  int mx = 0;
  for (int(i) = 1; (i) <= (n); (i)++) {
    mx = (mx > dp[i] ? mx : dp[i]);
  }
  printf("%d", n - mx);
  return 0;
}
