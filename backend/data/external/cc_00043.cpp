#include <bits/stdc++.h>
using namespace std;
vector<pair<long long, long long>> v, d;
long long ans;
int main() {
  int l, r;
  cin >> l >> r;
  if (l % 3 == 0 and l + 3 == r) {
    cout << 3;
    return 0;
  }
  if (l == r) {
    cout << l;
    return 0;
  }
  cout << 2;
  return 0;
}
