#include <bits/stdc++.h>
using namespace std;
const int N = 1007;
int n;
string s;
int cnt[2 * N];
int main() {
  cin >> n;
  cin >> s;
  s += s;
  int count_hamster = 0;
  for (int i = 0; i < 2 * n; i++) {
    if (s[i] == 'H') count_hamster += 1;
    cnt[i] = cnt[i - 1];
    if (s[i] == 'T') cnt[i] += 1;
  }
  count_hamster /= 2;
  int res = cnt[count_hamster - 1];
  for (int i = 1; i < 2 * n - count_hamster; i++) {
    res = min(res, cnt[i + count_hamster - 1] - cnt[i - 1]);
  }
  cout << res;
}
