#include <bits/stdc++.h>
using namespace std;
long long int prime[1000001], a[1000001];
vector<long long int> ar;
void sieve() {
  memset(prime, 1, sizeof(prime));
  prime[0] = prime[1] = 0;
  long long int i, j;
  for (i = 2; i <= sqrt(1000010); i++) {
    if (prime[i]) {
      for (j = i * 2; j < 1000010; j += i) {
        prime[j] = 0;
      }
    }
  }
  for (i = 0; i < 1000010; i++) {
    if (prime[i]) {
      ar.push_back(i);
    }
  }
}
int main() {
  sieve();
  long long int n, i, j, ans, temp;
  cin >> n;
  for (i = 2; i <= n; i++) {
    if (prime[i]) {
      a[i] = 0;
    } else {
      ans = 0;
      for (j = 2; j <= sqrt(i); j++) {
        if (i % j == 0) {
          ans += (i / j) * 4;
          temp = i / j;
          if (i != temp * temp) {
            ans += (i / temp) * 4;
          }
        }
      }
      a[i] = ans;
    }
  }
  ans = 0;
  for (i = 2; i <= n; i++) {
    ans += a[i];
  }
  cout << ans;
  return 0;
}
