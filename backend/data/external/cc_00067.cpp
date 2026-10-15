#include <bits/stdc++.h>
using namespace std;
struct Point {
  int x;
  int y;
};
int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<string> g;
  g.reserve(n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    g.push_back(s);
  }
  int i0 = -1;
  int j0 = -1;
  bool search = true;
  int c = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (search && g[i][j] == '.') {
        i0 = i;
        j0 = j;
        search = false;
      }
      c += (g[i][j] == '.');
    }
  int d = c - k;
  c = 0;
  vector<vector<bool> > visited(n, vector<bool>(m, false));
  stack<Point> s;
  s.push(Point{i0, j0});
  int dx[4] = {1, 0, -1, 0};
  int dy[4] = {0, 1, 0, -1};
  while (!s.empty()) {
    Point p = s.top();
    s.pop();
    if (visited[p.x][p.y]) continue;
    visited[p.x][p.y] = true;
    ++c;
    if (c > d) g[p.x][p.y] = 'X';
    for (int i = 0; i < 4; ++i) {
      int xx = p.x + dx[i];
      int yy = p.y + dy[i];
      if (xx >= 0 && xx < n && yy >= 0 && yy < m && !visited[xx][yy] &&
          g[xx][yy] == '.')
        s.push(Point{xx, yy});
    }
  }
  for (int i = 0; i < n; ++i) cout << g[i] << endl;
  return 0;
}
