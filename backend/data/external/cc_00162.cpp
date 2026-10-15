#include <bits/stdc++.h>
using namespace std;
template <typename A>
ostream &operator<<(ostream &cout, vector<A> const &v) {
  cout << "[";
  for (int i = 0; i < v.size(); i++) {
    if (i) cout << ", ";
    cout << v[i];
  }
  return cout << "]";
}
template <typename A, typename B>
ostream &operator<<(ostream &cout, pair<A, B> const &p) {
  return cout << "(" << p.first << ", " << p.second << ")";
}
template <typename A, typename B>
istream &operator>>(istream &cin, pair<A, B> &p) {
  cin >> p.first;
  return cin >> p.second;
}
void caseNumber(int x) { printf("Case %d: ", x); }
void yes() { cout << "YES\n"; }
void no() { cout << "NO\n"; }
int turnOn(int x, int pos) { return x | (1 << pos); }
int turnOff(int x, int pos) { return x & !(1 << pos); }
bool isOn(int x, int pos) { return (bool)(x & (1 << pos)); }
long long int const mod = 1e9 + 7;
long long int const inf = 1e17 + 9;
long long int const maxn = 1e6 + 7;
void solve() {
  int n;
  cin >> n;
  string ans = "";
  long long int a = 0, g = 0;
  for (int i = 0; i < n; i++) {
    long long int x, y;
    cin >> x >> y;
    if (abs(a + x - g) <= 500)
      a += x, ans += 'A';
    else
      g += y, ans += 'G';
  }
  cout << ans << endl;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  solve();
}
