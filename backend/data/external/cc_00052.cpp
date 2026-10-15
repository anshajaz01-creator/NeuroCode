#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int add(int x, int y, int CMOD = MOD) { return (0LL + x + y) % CMOD; }
int mult(int x, int y, int CMOD = MOD) { return (1LL * x * y) % CMOD; }
long long fast_expo(long long x, long long y, long long CMOD = MOD) {
  if (x == 0) return 0;
  if (y == 0) return 1;
  long long ans = fast_expo(x, y / 2, CMOD);
  ans = mult(ans, ans, CMOD);
  if (y & 1) ans = mult(ans, x, CMOD);
  return ans;
}
const int TAM = 2e5 + 100;
const long long INF = LLONG_MAX / 4;
int n;
int a[TAM];
int main() {
  ios_base ::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  int k;
  cin >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a + n);
  if (a[n / 2] == k) {
    cout << "0" << endl;
    return 0;
  }
  long long ans = 0;
  if (a[n / 2] < k) {
    for (int i = n / 2; i < n; i++) {
      ans += max(0, k - a[i]);
    }
  } else {
    for (int i = n / 2; i >= 0; i--) {
      ans += max(0, a[i] - k);
    }
  }
  cout << ans << endl;
  return 0;
}
