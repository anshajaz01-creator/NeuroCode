#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
const int INF = 0x3f3f3f3f;
template <class K, class V>
ostream& operator<<(ostream& out, const pair<K, V>& v) {
  out << '(' << v.first << ',' << v.second << ')';
  return out;
}
template <class C, class = typename C::iterator>
struct _cprint {
  using type = void;
};
template <>
struct _cprint<string> {};
template <class C, class = typename _cprint<C>::type>
ostream& operator<<(ostream& out, const C& v) {
  for (auto x : v) out << x << ' ';
  return out;
}
template <class C>
inline void chmax(C& x, const C& a) {
  if (x < a) x = a;
}
template <class C>
inline void chmin(C& x, const C& a) {
  if (x > a) x = a;
}
template <class C>
inline C mod(C a, C b) {
  return (a % b + b) % b;
}
int n, m, k;
vector<string> grid;
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};
void dfs(int i, int j) {
  if (k == 0) return;
  if (i < 0 || i >= n || j < 0 || j >= m) return;
  if (grid[i][j] != '.') return;
  grid[i][j] = 'T';
  for (int k = 0; k < 4; k++) dfs(i + di[k], j + dj[k]);
  if (k) grid[i][j] = 'X', k--;
}
int main() {
  cin >> n >> m >> k;
  grid.resize(n);
  for (int i = 0; i < n; i++) cin >> grid[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == '.') {
        dfs(i, j);
        goto stop;
      }
stop:
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 'T') grid[i][j] = '.';
  for (int i = 0; i < n; i++) cout << grid[i] << endl;
}
