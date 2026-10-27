#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int> > start[2 * 100000 + 1], ending[2 * 100000 + 1];
int main() {
  int n, k;
  cin >> n >> k;
  set<int> ans;
  set<pair<int, int>, greater<pair<int, int> > > st;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    start[x].push_back(make_pair(y, i));
    ending[y].push_back(make_pair(y, i));
  }
  for (int i = 1; i <= 2 * 100000; i++) {
    for (auto it : start[i]) {
      st.insert(it);
    }
    while (st.size() > k) {
      pair<int, int> a = *(st.begin());
      ans.insert(a.second);
      st.erase(st.begin());
    }
    for (auto it : ending[i]) {
      auto itt = ans.find(it.second);
      if (itt != ans.end()) continue;
      st.erase(it);
    }
  }
  cout << ans.size() << endl;
  for (auto it : ans) {
    cout << it << " ";
  }
  cout << endl;
}
