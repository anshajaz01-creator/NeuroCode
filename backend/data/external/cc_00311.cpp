#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e9;
const long long N = 5e2 + 1;
const long long mod = 1e9 + 7;
const long double eps = 1E-7;
string t;
long long int a, b, n, m, cnt, k, ans = 0;
vector<int> v, V;
int main() {
  string s, h;
  cin >> s >> h;
  if (s == "0" and h == "0") {
    cout << "OK";
    return 0;
  }
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '0') cnt++;
  }
  sort(s.begin(), s.end());
  if (cnt != 0) swap(s[0], s[cnt]);
  if (s == h)
    cout << "OK";
  else
    cout << "WRONG_ANSWER";
}
