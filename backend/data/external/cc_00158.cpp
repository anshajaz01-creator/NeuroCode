#include <bits/stdc++.h>
using namespace std;
int n, k;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  vector<int> s(1 << n);
  for (int i = 0; i < k; i++) {
    int b;
    cin >> b;
    b--;
    s[b] = 1;
  }
  auto iter = [&](int x, int y) {
    vector<int> a = {x >> 1, y >> 1};
    vector<int> b = {x & 1, y & 1};
    int cnt = (a[0] | a[1]) + (b[0] | b[1]);
    vector<pair<int, int>> res;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        int add = cnt + (a[i ^ 1] | b[j]);
        vector<int> c = {a[i ^ 1], b[j]};
        for (int t : c) {
          res.emplace_back(a[i] * 2 + t, add);
        }
      }
    }
    return res;
  };
  function<vector<int>(int, int)> dfs = [&](int l, int r) {
    vector<int> dp(4, -1);
    if (r == l + 1) {
      dp[s[l] + s[r] * 2] = s[l] | s[r];
      dp[s[r] + s[l] * 2] = s[l] | s[r];
      return dp;
    }
    int mid = (l + r) >> 1;
    vector<int> sl = dfs(l, mid);
    vector<int> sr = dfs(mid + 1, r);
    for (int cl = 0; cl < 4; cl++) {
      for (int cr = 0; cr < 4; cr++) {
        if (sl[cl] == -1 || sr[cr] == -1) continue;
        vector<pair<int, int>> ret = iter(cl, cr);
        for (pair<int, int> t : ret) {
          dp[t.first] = max(dp[t.first], sl[cl] + sr[cr] + t.second);
        }
      }
    }
    return dp;
  };
  vector<int> dp = dfs(0, (1 << n) - 1);
  int res = -1;
  for (int i = 0; i < 4; i++)
    if (dp[i] != -1) res = max(res, dp[i] + (i > 0));
  cout << res;
  return 0;
}
