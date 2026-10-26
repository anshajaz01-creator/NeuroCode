#include <bits/stdc++.h>
using namespace std;
int n, m, k;
set<int> M[200005];
int siz[200005], a[200005], b[200005], dele[200005], cnt, ans[200005];
void check(int u) {
  if (siz[u] >= k || dele[u]) return;
  cnt--;
  dele[u] = 1;
  queue<int> Q;
  Q.push(u);
  while (!Q.empty()) {
    int ty = Q.front();
    Q.pop();
    for (set<int>::iterator i = M[ty].begin(); i != M[ty].end(); i++) {
      int v = *i;
      siz[v]--;
      if (siz[v] < k && !dele[v]) {
        cnt--;
        Q.push(v);
        dele[v] = 1;
      }
    }
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &a[i], &b[i]);
    M[a[i]].insert(b[i]);
    M[b[i]].insert(a[i]);
    siz[a[i]]++;
    siz[b[i]]++;
  }
  cnt = n;
  for (int i = 1; i <= n; i++) check(i);
  ans[m] = cnt;
  for (int i = m; i >= 2; i--) {
    if (!dele[b[i]]) siz[a[i]]--;
    if (!dele[a[i]]) siz[b[i]]--;
    M[a[i]].erase(b[i]);
    M[b[i]].erase(a[i]);
    check(a[i]);
    check(b[i]);
    ans[i - 1] = cnt;
  }
  for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
  return 0;
}
