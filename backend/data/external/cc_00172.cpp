#include <bits/stdc++.h>
using namespace std;
const int PRIME = 151;
const long long MOD = 1e9 + 7;
const int MAXN = 1e3 + 5;
const int INF = 0x3f3f3f3f;
int n;
string s;
int main() {
  {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
  }
  cin >> n >> s;
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'T') cnt++;
  }
  int ans = INF;
  for (int i = 0; i < n; ++i) {
    int tt = 0;
    for (int j = 0; j < cnt; ++j) {
      tt += (s[(i + j) % n] == 'H');
    }
    ans = min(tt, ans);
  }
  cout << ans;
  return 0;
}
