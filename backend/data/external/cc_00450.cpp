#include <bits/stdc++.h>
using namespace std;
int a[200001], val[200001], ans = 0, T = 1;
int roun[200001], c[200001];
stack<int> s;
void DFS(int v, int rou) {
  roun[v] = rou;
  val[v] = T++;
  s.push(v);
  if (val[a[v]] == 0) {
    DFS(a[v], rou);
  } else if (roun[rou] == roun[a[v]]) {
    int x = 1e9;
    while (true) {
      int f = s.top();
      s.pop();
      x = min(x, c[f]);
      if (val[f] == val[a[v]]) break;
    }
    ans += x;
    return;
  } else
    return;
}
int main(int argc, char const *argv[]) {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> c[i];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
  }
  for (int i = 0; i < n; i++) {
    if (val[i] == 0) {
      while (!s.empty()) s.pop();
      T = 1;
      DFS(i, i);
    }
  }
  cout << ans << endl;
}
