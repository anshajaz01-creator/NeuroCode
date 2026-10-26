#include <bits/stdc++.h>
using namespace std;
int x[200010], y[200010];
set<int> s[200010];
queue<int> q, p;
bool inq[200010];
bool w[200010];
int ans[200010];
int n, m, k, sum;
void reset() {
  while (!q.empty()) q.pop();
  while (!p.empty()) inq[p.front()] = false, p.pop();
}
void BFS() {
  while (!q.empty()) {
    int now = q.front();
    w[now] = true;
    p.push(now);
    sum--;
    q.pop();
    for (set<int>::iterator i = s[now].begin(); i != s[now].end(); i++) {
      s[*i].erase(now);
      if (s[*i].size() < k && !inq[*i] && !w[*i]) inq[*i] = true, q.push(*i);
    }
  }
}
int main() {
  cin >> n >> m >> k;
  sum = n;
  for (int i = 1; i <= m; i++)
    cin >> x[i] >> y[i], s[x[i]].insert(y[i]), s[y[i]].insert(x[i]);
  for (int i = 1; i <= n; i++)
    if (s[i].size() < k) inq[i] = true, q.push(i);
  BFS();
  for (int i = m; i > 0; i--) {
    ans[i] = sum;
    reset();
    s[x[i]].erase(y[i]);
    s[y[i]].erase(x[i]);
    if (s[x[i]].size() < k && !w[x[i]]) inq[x[i]] = true, q.push(x[i]);
    if (s[y[i]].size() < k && !w[y[i]]) inq[y[i]] = true, q.push(y[i]);
    BFS();
  }
  for (int i = 1; i <= m; i++) cout << ans[i] << endl;
  return 0;
}
