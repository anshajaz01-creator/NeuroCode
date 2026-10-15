#include <bits/stdc++.h>
using namespace std;
int a[105], ma = -200;
bool cmp(int a, int b) { return abs(a) > abs(b); }
int main() {
  vector<int> ans;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    ma = max(ma, a[i]);
  }
  sort(a, a + n, cmp);
  int tmp = 1, ha_0 = 0;
  for (int i = 0; i < n; i++) {
    if (!a[i]) ha_0 = 1;
    if (a[i] > 0)
      ans.push_back(a[i]);
    else if (a[i] < 0) {
      if (tmp == 1)
        tmp = a[i];
      else {
        ans.push_back(tmp);
        ans.push_back(a[i]);
        tmp = 1;
      }
    }
  }
  if (!ans.size()) {
    cout << ma << endl;
  } else {
    for (int i = 0; i < ans.size(); i++) {
      if (i) cout << " ";
      cout << ans[i];
    }
    cout << endl;
  }
  return 0;
}
