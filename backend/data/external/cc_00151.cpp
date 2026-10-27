#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<string> split(const string& s, char c) {
  vector<string> v;
  stringstream ss(s);
  string x;
  while (getline(ss, x, c)) {
    v.emplace_back(x);
  }
  return move(v);
}
template <typename T, typename... Args>
inline string arrStr(T arr, int n) {
  stringstream s;
  s << "[";
  for (int i = 0; i < n - 1; i++) {
    s << arr[i] << ",";
  }
  s << arr[n - 1] << "]";
  return s.str();
}
inline void __evars_begin(int line) { cerr << "#" << line << ": "; }
template <typename T>
inline void __evars_out_var(vector<T> val) {
  cerr << arrStr(val, val.size());
}
template <typename T>
inline void __evars_out_var(T* val) {
  cerr << arrStr(val, 10);
}
template <typename T>
inline void __evars_out_var(T val) {
  cerr << val;
}
inline void __evars(vector<string>::iterator it) { cerr << endl; }
template <typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args) {
  cerr << it->substr((*it)[0] == ' ', it->length()) << "=";
  __evars_out_var(a);
  cerr << "; ";
  __evars(++it, args...);
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll n, m, k;
  cin >> n >> m >> k;
  vector<ll> p(n), s(n);
  for (ll i = 0; i < n; i++) {
    cin >> p[i];
  }
  for (ll i = 0; i < n; i++) {
    cin >> s[i];
  }
  vector<pair<ll, ll>> v[m + 1];
  for (ll i = 0; i < n; i++) {
    v[s[i]].push_back({p[i], i});
  }
  for (ll i = 1; i <= m; i++) {
    sort(v[i].begin(), v[i].end());
  }
  vector<ll> id(k);
  ll ans = 0;
  for (ll i = 0; i < k; i++) {
    cin >> id[i];
  }
  for (ll i = 0; i < k; i++) {
    id[i]--;
    ll school = s[id[i]];
    ll sz = v[school].size();
    if (v[school][sz - 1].second != id[i]) {
      ans++;
    }
  }
  cout << ans;
  return 0;
}
