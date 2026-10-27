#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:256000000")
using namespace std;
const int iinf = 1000000000;
const long long linf = 1000000000000000000LL;
const double dinf = 1e200;
const double eps = 1e-16;
const double PI = 3.14159265359;
inline int mymax(int a, int b) { return a < b ? b : a; }
inline int mymin(int a, int b) { return a > b ? b : a; }
inline long long mymax(long long a, long long b) { return a < b ? b : a; }
inline long long mymin(long long a, long long b) { return a > b ? b : a; }
inline long long myabs(long long a) { return a < 0 ? -a : a; }
int gcd(int a, int b) { return a ? gcd(b % a, a) : b; }
long long gcd(long long a, long long b) { return a ? gcd(b % a, a) : b; }
const int mod = 1000000007;
char ar[1100000];
int dp1[2][1100000];
int dp2[2][1100000];
int dp3[2][1100000];
int n, k;
void flip() {
  reverse(ar, ar + n);
  for (int i = 0; i < (n); ++i)
    if (ar[i] == 'B')
      ar[i] = 'W';
    else if (ar[i] == 'W')
      ar[i] = 'B';
}
void gen(int *dp1, int *dp2, int *dp3) {
  dp1[0] = 0;
  dp2[0] = 1;
  dp3[0] = 0;
  int dp0 = 1;
  int lb = -1;
  for (int i = 1; i <= n; ++i) {
    char c = ar[i - 1];
    if (c == 'W') lb = i - 1;
    if (c == 'X') dp0 = dp0 * 2 % mod;
    dp1[i] = dp1[i - 1];
    dp3[i] = 0;
    if (i - lb - 1 >= k && (i == k || ar[i - k - 1] != 'B')) {
      dp3[i] = dp2[i - k - (i == k ? 0 : 1)];
    }
    if (c == 'X') {
      dp1[i] = (dp1[i] * 2) % mod;
    }
    dp1[i] = (dp1[i] + dp3[i]) % mod;
    dp2[i] = (dp0 + mod - dp1[i]) % mod;
  }
}
int main() {
  scanf("%d%d\n%s", &n, &k, ar);
  gen(dp1[0], dp2[0], dp3[0]);
  flip();
  gen(dp1[1], dp2[1], dp3[1]);
  long long r = 0;
  for (int i = 0; i < (n); ++i) {
    r = (r + 1LL * dp1[0][i] * dp3[1][n - i]) % mod;
  }
  cout << r;
  return 0;
}
