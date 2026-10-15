#include <bits/stdc++.h>
using namespace std;
set<int> a[1000001];
long n, m;
bool used[1000001] = {0};
void dfs(int v = 0, int pre = 0) {
  used[v] = 1;
  set<int>::iterator it;
  set<int> RT;
  RT = a[v];
  for (it = RT.begin(); it != RT.end(); it++)
    if (!used[*it]) dfs(*it, v);
  if ((a[v].size()) % 2 == 1) {
    a[v].erase(pre);
  }
  bool f = 0;
  for (it = a[v].begin(); it != a[v].end(); it++) {
    a[*it].erase(v);
    if (!f)
      cout << (*it) << ' ' << v << ' ', f = 1;
    else
      f = 0, cout << (*it) << endl;
  }
}
int main() {
  cin >> n >> m;
  long s = 0;
  if (m % 2 == 1) {
    cout << "No solution";
    return 0;
  }
  for (int k = 1; k <= m; ++k) {
    long x, y;
    cin >> x >> y;
    a[x].insert(y);
    a[y].insert(x);
  }
  dfs(1);
  return 0;
}
