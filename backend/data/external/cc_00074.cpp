#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> edge[N];
int color[N], vis[N];
queue<int> test;
int n, m;
void init() {
  for (int i = 1; i <= n; i++) {
    vis[i] = 0;
    color[i] = -1;
  }
}
int work(int u) {
  vis[u] = 1;
  color[u] = 1;
  test.push(u);
  while (!test.empty()) {
    int ai = test.front();
    test.pop();
    for (int i = 0; i < (int)edge[ai].size(); i++) {
      int v = edge[ai][i];
      if (color[v] == -1) {
        color[v] = 1 - color[ai];
        vis[v] = 1;
        test.push(v);
      }
      if (color[v] == color[ai]) return 0;
    }
  }
  return 1;
}
int main() {
  vector<int> a, b;
  scanf("%d%d", &n, &m);
  init();
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  int flag = 1;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      flag = work(i);
      if (!flag) return 0 * printf("-1\n");
    }
  }
  for (int i = 1; i <= n; i++) {
    if (color[i] == 1) {
      a.push_back(i);
    } else {
      b.push_back(i);
    }
  }
  cout << (int)a.size() << endl;
  for (int i = 0; i < (int)a.size(); i++) {
    printf("%d ", a[i]);
  }
  cout << endl;
  cout << (int)b.size() << endl;
  for (int i = 0; i < (int)b.size(); i++) {
    printf("%d ", b[i]);
  }
}
