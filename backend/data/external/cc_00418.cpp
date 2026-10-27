#include <bits/stdc++.h>
using namespace std;
long long int mod = 1e9 + 7;
long long int power(long long int num, long long int r) {
  if (r == 0) return 1;
  if (r == 1) return num % mod;
  long long int ans = power(num, r / 2) % mod;
  if (r % 2 == 0) {
    return (ans * ans) % mod;
  }
  return (((ans * ans) % mod) * num) % mod;
}
long long int modinv(long long int num) { return power(num, mod - 2); }
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long int n;
  cin >> n;
  if (n == 1) {
    cout << "1";
    return 0;
  }
  cout << 2 * n * n - 2 * n + 1;
}
