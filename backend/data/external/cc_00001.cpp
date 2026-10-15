#include <bits/stdc++.h>
using namespace std;
int n, m, k;
struct Node {
  int x, y;
} a[200010];
int deg[200010];
bool fl[200010];
set<int> v[200010];
int ans;
int ans1[200010];
int pos[200010];
void solve(int x) {
  if (deg[x] >= k || !fl[x]) {
    return;
  }
  queue<int> q;
  q.push(x);
  fl[x] = 0;
  ans--;
  while (!q.empty()) {
    int y = q.front();
    q.pop();
    for (auto to : v[y]) {
      deg[to]--;
      if (deg[to] < k && fl[to]) {
        fl[to] = 0;
        q.push(to);
        ans--;
      }
    }
  }
}
int main(int argc, char const *argv[]) {
  scanf("%d%d%d", &n, &m, &k);
  memset(fl, 1, sizeof(fl));
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &a[i].x, &a[i].y);
    deg[a[i].x]++;
    deg[a[i].y]++;
    v[a[i].x].insert(a[i].y);
    v[a[i].y].insert(a[i].x);
  }
  ans = n;
  for (int i = 1; i <= n; i++) {
    solve(i);
  }
  for (int i = m; i; i--) {
    ans1[i] = ans;
    if (fl[a[i].y]) {
      deg[a[i].x]--;
    }
    if (fl[a[i].x]) {
      deg[a[i].y]--;
    }
    v[a[i].x].erase(a[i].y);
    v[a[i].y].erase(a[i].x);
    solve(a[i].x);
    solve(a[i].y);
  }
  for (int i = 1; i <= m; i++) {
    printf("%d\n", ans1[i]);
  }
  return 0;
}
