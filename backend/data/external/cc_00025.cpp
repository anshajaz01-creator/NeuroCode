#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long int n, m, i;
  cin >> n >> m;
  long long int a[n];
  for (i = 0; i < n; i++) cin >> a[i];
  vector<long long int> vect;
  vector<long long int> v[n + 5];
  for (i = 0; i < m; i++) {
    long long int u, vv;
    cin >> u >> vv;
    v[u].push_back(vv);
    if (vv == a[n - 1]) {
      vect.push_back(u);
    }
  }
  sort(vect.begin(), vect.end());
  for (i = 1; i <= n; i++) {
    sort(v[i].begin(), v[i].end());
  }
  for (i = n - 2; i >= 0; i--) {
    if (!binary_search(vect.begin(), vect.end(), a[i])) continue;
    for (long long int j = i + 1; j < n - 1; j++) {
      if (binary_search(v[a[j - 1]].begin(), v[a[j - 1]].end(), a[j])) {
        swap(a[j - 1], a[j]);
      } else
        break;
    }
  }
  long long int ans = 0;
  for (i = n - 2; i >= 0; i--) {
    if (binary_search(vect.begin(), vect.end(), a[i])) {
      ans++;
    } else
      break;
  }
  cout << ans << "\n";
}
