#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> data(n);
  for (int i = 0; i < (n); ++i) cin >> data[i];
  vector<int> tmp(n);
  for (int k = 0; k < (n - 1); ++k) {
    for (int j = 0; j < (n); ++j) tmp[j] = data[j];
    int ans = 0;
    for (int i = 0; i < (k + 1); ++i) {
      int next_index = 1;
      while (next_index * 2 + i < n) next_index <<= 1;
      tmp[next_index + i] += tmp[i];
      ans += tmp[i];
    }
    cout << ans << endl;
  }
  return 0;
}
