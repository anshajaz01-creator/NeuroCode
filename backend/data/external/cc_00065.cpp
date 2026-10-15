#include <bits/stdc++.h>
using namespace std;
int n, m, k, i, j, s, sx, sy, x, y, K;
char mp[505][505];
vector<int> a;
vector<int> b;
int r[4] = {0, 1, 0, -1}, w[4] = {1, 0, -1, 0};
int main() {
  scanf("%d%d%d", &n, &m, &K);
  for (i = 0; i < n; i++) scanf("%s", &mp[i]);
  s = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      if (mp[i][j] == '.') {
        sx = i;
        sy = j;
        s++;
      }
  a.push_back(sx);
  b.push_back(sy);
  mp[sx][sy] = 'X';
  k = -1;
  while (a.size() < s - K) {
    k++;
    x = a[k];
    y = b[k];
    for (i = 0; i < 4; i++) {
      if (x + r[i] >= 0 && x + r[i] < n && y + w[i] >= 0 && y + w[i] < m &&
          mp[x + r[i]][y + w[i]] == '.') {
        a.push_back(x + r[i]);
        b.push_back(y + w[i]);
        mp[x + r[i]][y + w[i]] = 'X';
      }
    }
  }
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      if (mp[i][j] == '.') mp[i][j] = 'X';
  for (i = 0; i < s - K; i++) mp[a[i]][b[i]] = '.';
  for (i = 0; i < n; i++) printf("%s\n", mp[i]);
}
