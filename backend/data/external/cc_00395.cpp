#include <bits/stdc++.h>
using namespace std;
long long int n, m, i, j, k, l, a[1000009], b[1000009], p[1000009], ans, cn, t,
    x, y, z, mx, mn, s;
char c[1000009], d[1000009], ch;
map<long long int, long long int> mp;
int main() {
  while (scanf("%I64d %I64d", &n, &k) != EOF) {
    memset(b, 0, sizeof(b));
    cn = 1;
    mp.clear();
    for (i = 0; i < n; i++) {
      scanf("%I64d", &a[i]);
      if (mp[a[i]] == 0) {
        mp[a[i]] = cn++;
      }
    }
    ans = i = 0;
    for (j = 0; j < n; j++) {
      b[mp[a[j]]]++;
      while (b[mp[a[j]]] == k) {
        ans += (n - j);
        b[mp[a[i]]]--;
        i++;
      }
    }
    printf("%I64d\n", ans);
  }
  return 0;
}
