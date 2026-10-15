#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > v;
const int N = 1e5 + 5;
int vis[N], inc[N];
bool bigraph;
void dfs(int n) {
  for (int i = 0; i < v[n].size(); i++) {
    if (vis[v[n][i]] == -1) {
      vis[v[n][i]] = !vis[n];
      dfs(v[n][i]);
    } else if (vis[v[n][i]] == vis[n]) {
      bigraph = 0;
    }
  }
}
int main() {
  int m, n;
  bigraph = 1;
  scanf("%d%d", &n, &m);
  memset(vis, -1, sizeof vis);
  int x, y;
  v.resize(n + 1);
  while (m--) {
    scanf("%d%d", &x, &y);
    v[x].push_back(y);
    v[y].push_back(x);
    inc[x] = 1;
    inc[y] = 1;
  }
  for (int i = 1; i <= n; i++) {
    if (vis[i] == -1 && inc[i]) {
      vis[i] = 1;
      dfs(i);
    }
  }
  if (bigraph) {
    vector<int> a, b;
    for (int i = 1; i <= n; i++)
      if (inc[i]) {
        if (vis[i] == 1)
          a.push_back(i);
        else
          b.push_back(i);
      }
    cout << a.size() << endl;
    for (int i = 0; i < a.size(); i++) cout << a[i] << " \n"[i == a.size() - 1];
    cout << b.size() << endl;
    for (int i = 0; i < b.size(); i++) cout << b[i] << " \n"[i == b.size() - 1];
  } else
    cout << "-1" << endl;
}
