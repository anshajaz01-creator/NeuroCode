#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> v(n), temp1(n), temp2(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    int indf = -1, indb = -1;
    for (int i = 0; i < n; i++) {
      if (v[i] < i) {
        break;
      }
      indf = i;
    }
    for (int i = n - 1; i >= 0; i--) {
      if (v[i] < (n - 1) - i) {
        break;
      }
      indb = i;
    }
    if (indb <= indf) {
      cout << "Yes\n";
    } else
      cout << "No\n";
  }
  return 0;
}
