#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
int n, m, a[N], b[N], f[N], g[N], L[N], R[N], s[N];
int sum(int a) { return s[a] - s[a - 1]; }
int sum(int a, int b) { return s[b] - s[a - 1]; }
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= m; i++) cin >> b[i], ++s[b[i]];
  for (int i = 1; i <= 200000; i++) s[i] += s[i - 1];
  sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
  a[0] = -1e8, a[n + 1] = 1e8;
  for (int i = 1; i <= n; i++)
    if (a[i] != a[i - 1] + 1)
      L[i] = i;
    else
      L[i] = L[i - 1];
  for (int i = n; i; i--)
    if (a[i] != a[i + 1] - 1)
      R[i] = i;
    else
      R[i] = R[i + 1];
  for (int i = 1; i <= n; i++) {
    f[i] = max(f[i], f[i - 1] + sum(a[i]));
    g[i] = max(g[i], f[i - 1] + sum(a[i]));
    for (int j = 1, len; j <= m && b[j] <= a[i]; j++)
      if ((len = a[i] - b[j]) < i) {
        g[i] = max(g[i], f[L[i - len] - 1] + sum(b[j], a[i]));
      }
    f[i] = max(f[i], g[i]);
    for (int j = m, len; j && b[j] >= a[i]; j--)
      if ((len = b[j] - a[i]) <= n - i) {
        f[R[i + len]] = max(f[R[i + len]], g[i] + sum(a[i] + 1, b[j]));
      }
  }
  cout << f[n] << endl;
}
