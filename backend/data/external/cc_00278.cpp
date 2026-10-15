#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const int MAX = 100005;
const int MOD = 1000000007;
inline bool isEq(double a, double b) { return abs(a - b) < EPS; }
inline double toRad(double deg) { return deg * PI / 180; }
inline double toDeg(double rad) { return rad * 180 / PI; }
inline void geti(int &_int) { scanf("%d", &_int); }
inline void getii(int &_int, int &_int2) { scanf("%d %d", &_int, &_int2); }
inline void getiii(int &_int, int &_int2, int &_int3) {
  scanf("%d %d %d", &_int, &_int2, &_int3);
}
inline void getl(long long &_ll) { scanf("%lld", &_ll); }
inline void getll(long long &_ll, long long &_ll2) {
  scanf("%lld %lld", &_ll, &_ll2);
}
inline void getlll(long long &_ll, long long &_ll2, long long &_ll3) {
  scanf("%lld %lld %lld", &_ll, &_ll2, &_ll3);
}
inline void getd(double &_double) { scanf("%lf", &_double); }
inline void getdd(double &_double, double &_double2) {
  scanf("%lf %lf", &_double, &_double2);
}
inline void getstr(char *str) { scanf("%s", str); }
vector<int> graph[105];
bool vis[105];
bool f = false;
void dfs(int u, int m) {
  if (vis[u]) return;
  vis[u] = true;
  if (u == m) {
    f = true;
    return;
  }
  for (int v : graph[u]) dfs(v, m);
}
int main(int argc, char *argv[]) {
  int n, m;
  getii(n, m);
  int a, b;
  for (int i = 0; i < n; i++) {
    getii(a, b);
    for (int j = a; j <= b; j++) {
      graph[a].push_back(j);
    }
  }
  dfs(0, m);
  if (f)
    cout << "YES";
  else
    cout << "NO";
  return 0;
}
