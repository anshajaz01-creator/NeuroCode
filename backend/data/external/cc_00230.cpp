#include <bits/stdc++.h>
using namespace std;
vector<int> vt[400000];
int vis[400000];
int a[400000];
int b[400000];
map<int, map<int, int> > ma;
int ans = 1;
int flag = 0;
int t, n, m;
void dfs(int x) {
  for (int i = 0; i < vt[x].size(); i++) {
    int ks = vt[x][i];
    if (flag) return;
    if (vis[ks] == 0) {
      a[ks] = a[x] ^ 1;
      vis[ks] = 1;
      ans++;
      if ((ma[x][ks] && a[x] == 0) || (!ma[x][ks] && a[x] == 1)) {
        b[ma[x][ks]] = 1;
      } else {
        b[ma[ks][x]] = 0;
      }
      dfs(ks);
    } else {
      if (a[x] == a[ks]) {
        flag = 1;
        return;
      }
      if ((ma[x][ks] && a[x] == 0) || (!ma[x][ks] && a[x] == 1)) {
        b[ma[x][ks]] = 1;
      } else {
        b[ma[ks][x]] = 0;
      }
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  ;
  {
    cin >> n >> m;
    ans = 1, flag = 0;
    for (int i = 1; i <= m; i++) {
      int x, y;
      cin >> x >> y;
      vt[x].push_back(y);
      vt[y].push_back(x);
      ma[x][y] = i;
    }
    for (int i = 1; i <= n; i++) {
      if (vis[i] == 0) {
        vis[i] = 1;
        dfs(i);
      }
    }
    if (flag == 0) {
      cout << "Yes" << endl;
      for (int i = 1; i <= m; i++) {
        cout << b[i];
      }
      cout << endl;
    } else
      cout << "No" << endl;
  }
  return 0;
}
