#include <bits/stdc++.h>
using namespace std;
vector<int> v[3 * 100001];
int get(int a, int b) {
  if (binary_search((v[a]).begin(), (v[a]).end(), b)) {
    return 1;
  } else {
    return 0;
  }
}
bool cheak[3 * 100001];
int main() {
  int n, m;
  cin >> n >> m;
  int A[n + 1];
  for (int i = 1; i < n + 1; i++) scanf("%d", &A[i]);
  vector<int> vv;
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    v[a].push_back(b);
    if (b == A[n]) {
      cheak[a] = true;
    }
  }
  for (int i = 0; i < 3 * 100001; i++) {
    if (v[i].size()) sort((v[i]).begin(), (v[i]).end());
  }
  int ans = 0;
  for (int i = n - 1; i >= 1; i--) {
    if (cheak[A[i]]) {
      int t = 0;
      for (int j : vv) {
        if (!get(A[i], j)) {
          t = 1;
          vv.push_back(A[i]);
          break;
        }
      }
      if (t) continue;
      ans++;
    } else {
      vv.push_back(A[i]);
    }
  }
  cout << ans << '\n';
}
