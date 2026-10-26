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
  int n, k, a[400010], j = 0;
  long long ans = 0;
  map<int, int> mp;
  mp.clear();
  scanf("%d %d", &n, &k);
  for (int(i) = 0; (i) < (n); (i)++) {
    scanf("%d", a + i);
  }
  for (int(i) = 0; (i) < (n); (i)++) {
    mp[a[i]]++;
    while (mp[a[i]] == k) {
      ans += n - i;
      mp[a[j]]--;
      j++;
    }
  }
  printf("%lld", ans);
  return 0;
}
