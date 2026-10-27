#include <bits/stdc++.h>
using namespace std;
int tp[200];
int num[200];
string ss[100];
char str[10];
int main(void) {
  string s;
  cin >> s;
  int k;
  cin >> k;
  for (int i = 1; i <= (k); ++i) {
    cin >> str;
    tp[str[0]] = tp[str[1]] = i;
    ss[i] = str;
  }
  s += '*';
  int cur = -1;
  int ans = 0;
  for (int i = 0; i < (s.size()); ++i) {
    if (cur != tp[s[i]]) {
      if (cur > 0) {
        ans += min(num[ss[cur][0]], num[ss[cur][1]]);
        num[ss[cur][0]] = num[ss[cur][1]] = 0;
      }
      cur = tp[s[i]];
      if (tp[s[i]] > 0) {
        num[s[i]]++;
      }
    } else {
      if (cur > 0) num[s[i]]++;
    }
  }
  cout << ans << endl;
}
