#include <bits/stdc++.h>
using namespace std;
long long mod = 1000000007;
int n, m, k;
string s[505];
int vis[505][505];
int c = 0;
int cc = 0;
void dfs(int x, int y) {
  if (c == cc - k) return;
  vis[x][y] = 1;
  c++;
  if (x + 1 < n && s[x + 1][y] == '.' && !vis[x + 1][y]) {
    dfs(x + 1, y);
  }
  if (x - 1 >= 0 && s[x - 1][y] == '.' && !vis[x - 1][y]) {
    dfs(x - 1, y);
  }
  if (y + 1 < m && s[x][y + 1] == '.' && !vis[x][y + 1]) {
    dfs(x, y + 1);
  }
  if (y - 1 >= 0 && s[x][y - 1] == '.' && !vis[x][y - 1]) {
    dfs(x, y - 1);
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (s[i][j] == '.') cc++;
    }
  }
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (s[i][j] == '.') {
        dfs(i, j);
        break;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (vis[i][j] == 0 && s[i][j] == '.') {
        s[i][j] = 'X';
      }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << s[i];
    cout << endl;
  }
  return 0;
}
