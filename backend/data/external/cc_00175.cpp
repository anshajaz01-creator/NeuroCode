#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> a(n, 0);
  string s;
  cin >> s;
  int one = 0;
  for (int i = 0; i < s.size(); ++i)
    if (s[i] == 'T') {
      a[i] = 1;
      one++;
    }
  int best = 1000000;
  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < one; ++j) {
      int ind = (i + j) % n;
      cnt += (a[ind] == 0);
    }
    best = min(best, cnt);
  }
  cout << best << endl;
  return 0;
}
