#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
const int mod = 998244353;
const long long inf = 1e18;
int a[maxn], b[maxn];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
  int tp = a[m] + b[1];
  int p = n, ans = 0;
  for (int i = 1; i < m; i++)
    if (a[i] + b[p] <= tp) {
      p--;
      ans++;
    }
  cout << m - ans << endl;
  return 0;
}
