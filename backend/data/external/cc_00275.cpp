#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> a[100001];
vector<int> e[100001];
vector<int> b;
int c, d, ans;
int cyc;
bool vis[100001];
int used[100001];
void dfs(int x) {
  if (vis[x]) return;
  b.push_back(x);
  vis[x] = true;
  for (int i = 0; i < e[x].size(); i++) {
    dfs(e[x][i]);
  }
}
void dfs2(int xx) {
  used[xx] = 1;
  for (int i = 0; i < a[xx].size(); i++) {
    if (used[a[xx][i]] == 1) cyc = 1;
    if (!used[a[xx][i]]) dfs2(a[xx][i]);
  }
  used[xx] = 2;
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> c >> d;
    a[c].push_back(d);
    e[c].push_back(d);
    e[d].push_back(c);
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      cyc = 0;
      b.clear();
      dfs(i);
      for (int j = 0; j < b.size(); j++) {
        if (!used[b[j]]) dfs2(b[j]);
      }
      ans += b.size() - 1 + cyc;
    }
  }
  cout << ans;
  return 0;
}
