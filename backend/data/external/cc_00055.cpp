#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, s;
  vector<long long> v;
  cin >> n >> s;
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    v.push_back(val);
  }
  sort(v.begin(), v.end());
  int mid = n / 2;
  long long m = v[mid];
  int idx = lower_bound(v.begin(), v.end(), s) - v.begin();
  long long ans = 0;
  int i = mid;
  bool found = false;
  while (i < idx) {
    ans += (s - v[i]);
    found = true;
    i++;
  }
  if (!found) {
    while (i >= idx) {
      ans += (v[i] - s);
      i--;
    }
  }
  cout << ans << endl;
  return 0;
}
