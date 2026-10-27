#include <bits/stdc++.h>
const double eps = 1e-9;
const double pi = acos(-1);
const int oo = 1000000000;
const int mod = 1000000007;
const double E = 2.7182818284590452353602874713527;
using namespace std;
char a[1000005];
int f[1000005][2][2], s1[1000005], s2[1000005];
int main() {
  int n, k, s = 1, ans = 0;
  cin >> n >> k;
  scanf("%s", a + 1);
  f[0][0][1] = 1;
  for (int i = 1; i <= n; i++) {
    if (a[i] == 'X') s = s * 2 % mod;
    s1[i] = s1[i - 1] + (a[i] == 'B');
    s2[i] = s2[i - 1] + (a[i] == 'W');
    if (a[i] == 'B' || a[i] == 'X') {
      f[i][0][0] = (f[i - 1][0][0] + f[i - 1][0][1]) % mod;
      f[i][1][0] = (f[i - 1][1][0] + f[i - 1][1][1]) % mod;
    }
    if (a[i] == 'W' || a[i] == 'X') {
      f[i][0][1] = (f[i - 1][0][0] + f[i - 1][0][1]) % mod;
      f[i][1][1] = (f[i - 1][1][0] + f[i - 1][1][1]) % mod;
    }
    if (i >= k && s2[i] - s2[i - k] == 0) {
      f[i][0][0] = (f[i][0][0] - f[i - k][0][1] + mod) % mod;
      f[i][1][0] = (f[i][1][0] + f[i - k][0][1]) % mod;
    }
    if (i >= k && s1[i] - s1[i - k] == 0)
      f[i][1][1] = (f[i][1][1] - f[i - k][1][0] + mod) % mod;
  }
  cout << (s -
           (((f[n][0][0] + f[n][0][1]) % mod + f[n][1][0]) % mod + f[n][1][1]) %
               mod +
           mod) %
              mod
       << endl;
  return 0;
}
