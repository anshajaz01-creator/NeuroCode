#include <bits/stdc++.h>
using namespace std;
int a[1000006], c[1000006];
int vis[1000006];
int ans[1000006];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  int i;
  int sum = 0;
  cin >> n;
  for (i = 1; i <= n; i++) cin >> c[i];
  for (i = 1; i <= n; i++) cin >> a[i];
  for (i = 1; i <= n; i++) {
    int x = i;
    while (!vis[x]) {
      vis[x] = 1;
      x = a[x];
    }
    if (vis[x] > 1) {
      int p = ans[x];
      x = i;
      while (vis[x] == 1) {
        vis[x] = 2;
        ans[x] = p;
        x = a[x];
      }
      continue;
    }
    int minm = 1000006;
    while (vis[x] == 1) {
      vis[x] = 2;
      minm = min(minm, c[x]);
      x = a[x];
    }
    x = i;
    while (vis[x] < 3) {
      vis[x] = 3;
      ans[x] = minm;
      x = a[x];
    }
    sum += minm;
  }
  cout << sum;
  return 0;
}
