#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e5, M = 2000, V = (int)2e5;
int monster[N], star[M], f[N], g[N], blockBegin[N], blockEnd[N], n, m;
bool checkMax(int &a, int b) { return a < b ? a = b, true : false; }
void enter() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> monster[i];
    --monster[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> star[i];
    --star[i];
  }
}
void prepare() {
  sort(monster, monster + n);
  sort(star, star + m);
  for (int i = 0; i < n;) {
    int j = i;
    while (j < n && monster[j] == monster[i] + (j - i)) ++j;
    for (int k = i; k < j; ++k) {
      blockBegin[k] = i;
      blockEnd[k] = j - 1;
    }
    i = j;
  }
}
void solve() {
  for (int i = 0; i < n; ++i) {
    if (blockBegin[i] > 0) checkMax(g[i], f[blockBegin[i] - 1]);
    int starAfter = upper_bound(star, star + m, monster[i]) - star;
    for (int firstStar = starAfter - 1; firstStar >= 0; --firstStar) {
      int distance = monster[i] - star[firstStar];
      int firstMonster = i - distance;
      if (firstMonster < 0) break;
      int previousMonster = blockBegin[firstMonster] - 1;
      checkMax(g[i], (previousMonster < 0 ? 0 : f[previousMonster]) +
                         (starAfter - firstStar));
    }
    for (int lastStar = starAfter; lastStar < m; ++lastStar) {
      int distance = star[lastStar] - monster[i];
      int lastMonster = i + distance;
      if (lastMonster < n)
        checkMax(f[lastMonster], g[i] + (lastStar - starAfter + 1));
      else
        break;
    }
    if (i > 0) checkMax(f[i], f[i - 1]);
    checkMax(f[i], g[i]);
  }
  cout << f[n - 1];
}
int main() {
  ios::sync_with_stdio(false);
  enter();
  prepare();
  solve();
  return 0;
}
