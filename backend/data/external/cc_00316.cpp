#include <bits/stdc++.h>
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
int main() {
  int T;
  cin >> T;
  while (T--) {
    ll n, c = 0;
    cin >> n;
    ll a[n];
    map<ll, ll> m, m1;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      m[a[i]] = -1;
      m1[a[i]]++;
    }
    ll Rekhe_De = 0;
    ll Rekhe_de = 0;
    for (int i = 0; i <= 101; i++) {
      if (m[i] == 0 && c == 0) {
        Rekhe_De = i;
        ++c;
        break;
      } else if (m1[i] > 0)
        m1[i]--;
    }
    for (int i = 0; i <= 101; ++i) {
      if (m1[i] == 0) {
        Rekhe_de = i;
        break;
      }
    }
    cout << Rekhe_De + Rekhe_de << endl;
  }
}
