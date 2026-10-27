#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<priority_queue<int>> schools(m + 1);
  int arr[2][n + 1];
  for (int i = 1; i <= n; i++) cin >> arr[0][i];
  for (int i = 1; i <= n; i++) cin >> arr[1][i];
  for (int i = 1; i <= n; i++) {
    int s = arr[1][i];
    schools[s].push(arr[0][i]);
  }
  vector<int> v(k);
  for (int i = 0; i < k; i++) cin >> v[i];
  int ans = 0;
  for (int i = 0; i < k; i++) {
    int id = v[i];
    int s = arr[1][id];
    if (arr[0][id] != schools[s].top()) ans++;
  }
  cout << ans;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}
