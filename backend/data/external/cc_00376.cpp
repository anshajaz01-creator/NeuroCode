#include <bits/stdc++.h>
using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;
using PII = pair<int, int>;
using LL = long long;
using VL = vector<LL>;
using VVL = vector<VL>;
using PLL = pair<LL, LL>;
using VS = vector<string>;
template <class S, class T>
istream& operator>>(istream& is, pair<S, T>& p) {
  return is >> p.first >> p.second;
}
template <class S, class T>
ostream& operator<<(ostream& os, const pair<S, T>& p) {
  return os << p.first << " " << p.second;
}
template <class T>
void maxi(T& x, T y) {
  if (x < y) x = y;
}
template <class T>
void mini(T& x, T y) {
  if (x > y) x = y;
}
const double EPS = 1e-10;
const double PI = acos(-1.0);
const LL MOD = 1e9 + 7;
int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);
  LL K;
  cin >> K;
  cin.ignore();
  string N;
  cin >> N;
  LL acc = 0;
  VL cnt(10);
  for (int i = (0); i < (int((N).size())); ++i) {
    cnt['9' - N[i]]++;
    acc += N[i] - '0';
  }
  LL ans = 0, i = 9;
  while (K > acc) {
    while (!cnt[i]) --i;
    ++ans;
    acc += i;
    --cnt[i];
  }
  cout << ans << endl;
  return 0;
}
