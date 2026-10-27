#include <bits/stdc++.h>
using namespace std;
const long long int mod = 1e9 + 7;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, i;
  cin >> n;
  vector<int> v(n);
  for (i = 0; i < n; ++i) cin >> v[i];
  if (n == 1)
    cout << v[0] << "\n";
  else {
    int z = 0, p = 0, ng = 0;
    vector<int> vp, vng;
    for (i = 0; i < n; ++i) {
      if (v[i] > 0)
        vp.push_back(v[i]), p++;
      else if (v[i] == 0)
        z++;
      else
        vng.push_back(v[i]), ng++;
    }
    sort(vp.begin(), vp.end(), greater<int>());
    sort(vng.begin(), vng.end());
    if (p == 1 and ng == 0)
      cout << vp[0] << "\n";
    else if (p == 0 and ng == 0)
      cout << 0 << "\n";
    else if (p == 0 and ng == 1) {
      if (z > 0)
        cout << 0 << "\n";
      else
        cout << vng[0];
    } else if (p == 1 and ng == 1)
      cout << vp[0] << "\n";
    else {
      if (ng % 2) ng -= 1;
      for (i = 0; i < ng; ++i) {
        cout << vng[i] << " ";
      }
      for (i = 0; i < p; ++i) {
        cout << vp[i] << " ";
      }
      cout << "\n";
    }
  }
  return 0;
}
