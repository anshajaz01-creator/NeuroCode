#include <bits/stdc++.h>
using namespace std;
int __tag__ = 0;
template <class L, class R>
ostream& operator<<(ostream& out, pair<L, R>& p) {
  return out << p.first << " " << p.second;
}
template <class T>
ostream& operator<<(ostream& out, vector<T>& vec) {
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    out << ((it != begin(vec)) ? " " : "") << *it;
  }
  return out;
}
const int maxn = 3e5 + 5;
const long long mod = 998244353;
void solve() {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<vector<pair<int, int>>> G(n);
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    G[u].push_back({v, i});
    G[v].push_back({u, -i});
  }
  bool flag = true;
  vector<int> ans(m + 1, -1), vis(n, 0);
  queue<pair<int, int>> Q;
  Q.push({0, 0});
  while (!Q.empty()) {
    int u = Q.front().first, type = Q.front().second;
    Q.pop();
    vis[u] = 1;
    for (auto& e : G[u]) {
      int v = e.first, i = e.second;
      if (i > 0) {
        if (ans[i] == -1) {
          ans[i] = type;
          Q.push({v, 1 - type});
        } else if (ans[i] != type) {
          flag = false;
          break;
        }
      } else {
        if (ans[-i] == -1) {
          ans[-i] = 1 - type;
          Q.push({v, 1 - type});
        } else if (ans[-i] != 1 - type) {
          flag = false;
          break;
        }
      }
    }
    if (!flag) break;
  }
  if (flag) {
    puts("YES");
    for (int i = 1; i <= m; i++) {
      cout << ans[i];
    }
    cout << '\n';
  } else {
    puts("NO");
  }
}
int main() {
  int T = 1;
  double abc = 213213213;
  abc++;
  ++abc;
  int sdasdhasd = 21321321;
  abc--;
  abc = abs(abc);
  for (int Case = (1), _TOP = (T); Case <= _TOP; Case++) {
    solve();
  }
}
