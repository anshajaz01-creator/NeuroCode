#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007LL;
int t, n;
map<int, set<int>> ps;
int main() {
  cin >> t;
  for (int cas = 1; cas <= t; ++cas) {
    cin >> n;
    ps.clear();
    for (int i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      ps[x].insert(y);
    }
    bool ok = true;
    string ans = "";
    int prey = 0;
    int prex = 0;
    for (auto itr = ps.begin(); itr != ps.end(); ++itr) {
      if (itr == ps.begin()) {
        int det = (itr->first) - prex;
        for (int i = 1; i <= det; ++i) {
          ans += "R";
        }
        int v = *((itr->second).rbegin());
        for (int i = 1; i <= v - prey; ++i) {
          ans += "U";
        }
        prex = itr->first;
        prey = v;
        continue;
      }
      auto pre = itr;
      pre--;
      int v1 = *((itr->second).begin());
      int v2 = *((pre->second).rbegin());
      if (v1 < v2) {
        ok = false;
        break;
      }
      int det = (itr->first) - prex;
      for (int i = 1; i <= det; ++i) {
        ans += "R";
      }
      int v = *((itr->second).rbegin());
      for (int i = 1; i <= v - prey; ++i) {
        ans += "U";
      }
      prex = itr->first;
      prey = v;
    }
    if (!ok)
      cout << "NO" << endl;
    else {
      cout << "YES" << endl;
      cout << ans << endl;
    }
  }
  return 0;
}
