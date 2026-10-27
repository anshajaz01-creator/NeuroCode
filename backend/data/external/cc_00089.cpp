#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
const long long N = 1e5 + 33;
void solve() {
  int n, x;
  cin >> n;
  vector<int> v, pref;
  map<int, int> mp;
  for (int i = 0; i < n; i++) {
    cin >> x;
    if (mp[x] == 0) v.push_back(x);
    mp[x]++;
  }
  pref = vector<int>(v.size());
  pref[0] = mp[v[0]];
  for (int i = 1; i < v.size(); i++) {
    pref[i] = pref[i - 1] + mp[v[i]];
  }
  int opt = n / 2;
  int id = upper_bound(pref.begin(), pref.end(), opt) - pref.begin() - 1;
  int g = mp[v[0]];
  int pos_s = lower_bound(pref.begin(), pref.end(), g + g + 1) - pref.begin();
  if (pos_s >= id || id < 2) {
    cout << 0 << " " << 0 << " " << 0;
  } else {
    int s = pref[pos_s] - g, b = pref[id] - pref[pos_s];
    if (g >= s || g >= b)
      cout << 0 << " " << 0 << " " << 0;
    else
      cout << g << " " << s << " " << b;
  }
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
    cout << endl;
  }
}
