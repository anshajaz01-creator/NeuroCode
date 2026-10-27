#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n;
  cin >> n;
  multiset<int> S;
  for (int i = 1; i <= n; ++i) {
    int t;
    cin >> t;
    S.insert(t);
  }
  int Ans = 0;
  for (int i = 0;; ++i) {
    multiset<int>::iterator kksk = S.find(i);
    if (kksk != S.end())
      S.erase(kksk);
    else {
      Ans += i;
      break;
    }
  }
  for (int i = 0;; ++i) {
    auto kksk = S.find(i);
    if (kksk != S.end())
      S.erase(kksk);
    else {
      Ans += i;
      break;
    }
  }
  cout << Ans << endl;
}
int main() {
  int T;
  cin >> T;
  while (T--) solve();
  return 0;
}
