#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
using namespace std;
const int MOD = 1000000007;
const long long INF = 1e18;
const int MX = 200005;
const long double PI = 4 * atan((long double)1);
template <class T>
void ckmin(T &a, T b) {
  a = min(a, b);
}
template <class T>
void ckmax(T &a, T b) {
  a = max(a, b);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  while (n--) {
    string second, t;
    cin >> second >> t;
    vector<pair<char, int>> c;
    vector<int> pos[26];
    for (int i = 0; i < ((int)second.size()); i++) {
      c.push_back({second[i], i});
      pos[second[i] - 'A'].push_back(i);
    }
    sort(begin(c), end(c));
    bool found = false;
    for (int i = 0; i < ((int)second.size()); i++) {
      if (c[i].first != second[i]) {
        for (auto &curr : pos[c[i].first - 'A']) {
          if (curr <= i) continue;
          swap(second[i], second[curr]);
          if (second < t) {
            found = true;
            break;
          } else {
            swap(second[i], second[curr]);
          }
        }
        if (found) break;
      }
    }
    if (second < t)
      cout << second << "\n";
    else
      cout << "---"
           << "\n";
  }
}
