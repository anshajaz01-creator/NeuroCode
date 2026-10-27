#include <bits/stdc++.h>
using namespace std;
map<int, int> m;
set<int> q;
int a[400005];
int main() {
  long long n, k, c = 0, s = 0;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (++m[a[i]] == k) q.insert(a[i]);
    while (q.size()) {
      s += n - i;
      if (--m[a[c++]] == k - 1) q.erase(a[c - 1]);
    }
  }
  cout << s;
}
