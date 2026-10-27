#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n, m, val = 0;
  cin >> n >> m;
  while (n--) {
    int a, b;
    cin >> a >> b;
    if (a <= val) {
      val = max(val, b);
    }
  }
  if (val >= m) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
  return;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  solve();
  return 0;
}
