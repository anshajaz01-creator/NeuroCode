#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110;
int n, p[MAXN][MAXN];
long long gcd(long long a, long long b) {
  if (!b) return a;
  return gcd(b, a % b);
}
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
int main() {
  scanf("%d", &n);
  for (int i = (0); i < int(n); i++)
    for (int j = (0); j < int(n); j++) p[i][j] = (1 << 20);
  for (int i = (0); i < int(n); i++) {
    int a;
    scanf("%d", &a);
    a--;
    p[i][a] = 1;
  }
  for (int k = (0); k < int(n); k++)
    for (int i = (0); i < int(n); i++)
      for (int j = (0); j < int(n); j++)
        p[i][j] = min(p[i][j], p[i][k] + p[k][j]);
  for (int i = (0); i < int(n); i++) {
    if (p[i][i] >= (1 << 20)) {
      puts("-1");
      return 0;
    }
  }
  vector<int> v;
  for (int i = (0); i < int(n); i++)
    (p[i][i] % 2) ? v.push_back(p[i][i]) : v.push_back(p[i][i] / 2);
  long long ans = 1;
  for (int i = (0); i < int((int)v.size()); i++)
    ans = lcm(ans, (long long)v[i]);
  printf("%lld\n", ans);
  return 0;
}
