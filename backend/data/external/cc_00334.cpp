#include <bits/stdc++.h>
using namespace std;
template <class T>
T abs(T x) {
  return x > 0 ? x : -x;
}
template <class T>
T gcd(T a, T b) {
  return a ? gcd(b % a, a) : b;
}
template <class T>
T sqr(T a) {
  return a * a;
}
template <class T>
T sgn(T a) {
  return a > 0 ? 1 : (a < 0 ? -1 : 0);
}
const double pi = acos(-1.0);
int n;
int m;
const int N = 50 + 3;
const int mod = 1e9 + 7;
int was[N][N][N][N];
int f[N][N][N][N];
int g[2][N], c[N], pw2[N];
int p;
int go(array<int, 4> a) {
  int i = a[0] + a[1] + a[2] + a[3];
  if (i == n) {
    return (a[1] + a[3]) % 2 == p;
  }
  auto& cur_was = was[a[0]][a[1]][a[2]][a[3]];
  auto& cur_f = f[a[0]][a[1]][a[2]][a[3]];
  if (cur_was) return cur_f;
  cur_was = true;
  auto ac = a;
  int cur;
  if (c[i] == -1 || c[i] == 0) {
    ac[0]++;
    cur = ((long long)pw2[i - a[3]] * g[0][a[3]]) % mod;
    cur_f = (cur_f + (long long)go(ac) * cur) % mod;
    ac[0]--;
    ac[1]++;
    cur = ((long long)pw2[i - a[3]] * g[1][a[3]]) % mod;
    cur_f = (cur_f + (long long)go(ac) * cur) % mod;
    ac[1]--;
  }
  if (c[i] == -1 || c[i] == 1) {
    ac[2]++;
    cur = ((long long)pw2[i - a[1]] * g[0][a[1]]) % mod;
    cur_f = (cur_f + (long long)go(ac) * cur) % mod;
    ac[2]--;
    ac[3]++;
    cur = ((long long)pw2[i - a[1]] * g[1][a[1]]) % mod;
    cur_f = (cur_f + (long long)go(ac) * cur) % mod;
    ac[3]--;
  }
  return cur_f;
}
int main() {
  cin >> n >> p;
  for (int i = 0; i < n; i++) cin >> c[i];
  pw2[0] = 1;
  for (int i = 0; i < n; i++) pw2[i + 1] = (pw2[i] * 2ll) % mod;
  g[1][0] = 1;
  for (int i = 1; i <= n; i++) g[0][i] = g[1][i] = pw2[i - 1];
  cout << go({0, 0, 0, 0}) << endl;
  return 0;
}
