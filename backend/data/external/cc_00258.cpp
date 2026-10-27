#include <bits/stdc++.h>
using namespace std;
double const eps = 1e-10;
int const INF = 100000;
int const MOD = 1000000007;
int const MAX = 1000 * 100 + 5;
string s;
int a[30];
int main() {
  int n, i, ans = 0;
  cin >> s;
  cin >> n;
  memset(a, -1, sizeof(a));
  char c1, c2;
  for (i = 0; i < n; ++i) {
    cin >> c1 >> c2;
    a[c1 - 'a'] = c2 - 'a';
    a[c2 - 'a'] = c1 - 'a';
  }
  for (i = 0; i < s.size();) {
    while (i < s.size() && a[s[i] - 'a'] == -1) ++i;
    int start = i;
    int k1 = 0, k2 = 0;
    while (i < s.size() &&
           (s[i] == s[start] || s[i] == a[s[start] - 'a'] + 'a')) {
      if (s[i] == s[start]) ++k1;
      if (s[i] == a[s[start] - 'a'] + 'a') ++k2;
      ++i;
    }
    ans += min(k1, k2);
  }
  cout << ans;
  return 0;
}
