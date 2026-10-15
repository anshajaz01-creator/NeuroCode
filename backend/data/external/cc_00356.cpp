#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T& x) {
  int f = 0, c = getchar();
  x = 0;
  while (!isdigit(c)) f |= c == '-', c = getchar();
  while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
  if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
  read(x);
  read(args...);
}
template <typename T>
void write(T x) {
  if (x < 0) x = -x, putchar('-');
  if (x > 9) write(x / 10);
  putchar(x % 10 + 48);
}
template <typename T>
void writes(T x) {
  write(x);
  putchar(' ');
}
template <typename T>
void writeln(T x) {
  write(x);
  puts("");
}
template <typename T>
inline bool chkmin(T& x, const T& y) {
  return y < x ? (x = y, true) : false;
}
template <typename T>
inline bool chkmax(T& x, const T& y) {
  return x < y ? (x = y, true) : false;
}
const int maxn = (int)3e5 + 10;
const long long inf = (long long)1e18;
const int mod = (int)1e9 + 7;
int n, a[55][55], dp[55][55][55][55];
char ch;
int dfs(int x1, int y1, int x2, int y2) {
  if (x1 > x2 || y1 > y2) return 0;
  if (~dp[x1][y1][x2][y2]) return dp[x1][y1][x2][y2];
  if (x1 == x2 && y1 == y2) return a[x1][y1];
  int res = max(x2 - x1 + 1, y2 - y1 + 1);
  for (int i = (x1); i < (x2); i++) {
    res = min(res, dfs(x1, y1, i, y2) + dfs(i + 1, y1, x2, y2));
  }
  for (int i = (y1); i < (y2); i++) {
    res = min(res, dfs(x1, y1, x2, i) + dfs(x1, i + 1, x2, y2));
  }
  return dp[x1][y1][x2][y2] = res;
}
int main() {
  read(n);
  for (int i = (1); i < (n + 1); i++) {
    for (int j = (1); j < (n + 1); j++) {
      cin >> ch;
      a[i][j] = (ch == '#');
    }
  }
  memset(dp, -1, sizeof dp);
  writeln(dfs(1, 1, n, n));
}
