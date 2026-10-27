#include <bits/stdc++.h>
using namespace std;
vector<long long> v, t;
int main() {
  long long n;
  scanf("%I64d", &n);
  ;
  v.resize(n);
  for (int i = 0; i < n; ++i) scanf("%I64d", &v[i]);
  ;
  t = v;
  sort((t).begin(), (t).end());
  long long cnt = 0;
  for (int i = 0; i < n; ++i)
    if (v[i] != t[i]) cnt++;
  cout << (cnt > 2 ? "NO" : "YES");
  return 0;
}
