#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, k, pre[N], dp[N];
vector<pair<int, int> > v[N];
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1, l, r; i <= n; i++) {
    cin >> l >> r;
    v[l].push_back(pair<int, int>(r, i));
    pre[l]++;
    pre[r + 1]--;
  }
  for (int i = 1; i <= 2e5; i++) {
    pre[i] += pre[i - 1];
  }
  int now = 0;
  priority_queue<pair<int, int> > q;
  vector<int> ans;
  for (int i = 1; i <= 2e5; i++) {
    for (auto x : v[i]) {
      q.push(x);
    }
    while (pre[i] - now > k) {
      now++;
      dp[q.top().first]++;
      ans.push_back(q.top().second);
      q.pop();
    }
    now -= dp[i];
  }
  cout << ans.size() << endl;
  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << endl;
}
