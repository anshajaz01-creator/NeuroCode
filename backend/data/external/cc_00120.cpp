#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cin.tie(0), cout.tie(0),
      cout.precision(15);
  int t;
  cin >> t;
  while (t--) {
    int n, x;
    set<int> s;
    cin >> n;
    for (int i = int(0); i < int(n); i++) {
      cin >> x;
      s.insert(x);
    }
    cout << s.size() << '\n';
  }
  return 0;
}
