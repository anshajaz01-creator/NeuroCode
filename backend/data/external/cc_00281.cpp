#include <bits/stdc++.h>
using namespace std;
const long long mod = (long long)1e9 + 7;
int vis[105], n, m;
int main() {
  cin >> n >> m;
  int r = 0, flag = 0;
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    if (r < x)
      flag = 1;
    else
      r = max(r, y);
  }
  if (r == m && flag == 0)
    printf("YES\n");
  else
    printf("NO\n");
  return 0;
}
