#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
int n, m, k;
int sum[105][105];
int vis[105][105];
void solve(int m) {
  int Min = 1 << 29;
  int x, y1, y2;
  for (int i = 1; i <= k; i++) {
    for (int j = 0; j + m <= k; j++) {
      if (vis[i][j + m] - vis[i][j] == m) {
        if (sum[i][j + m] - sum[i][j] < Min) {
          Min = sum[i][j + m] - sum[i][j];
          x = i;
          y1 = j + 1;
          y2 = j + m;
        }
      }
    }
  }
  if (Min == 1 << 29)
    printf("-1\n");
  else {
    printf("%d %d %d\n", x, y1, y2);
    for (int j = y1; j <= y2; j++) vis[x][j] -= j - y1 + 1;
    for (int j = y2 + 1; j <= k; j++) vis[x][j] -= m;
  }
}
int main() {
  scanf("%d%d", &n, &k);
  int c = k / 2 + 1;
  for (int i = 1; i <= k; i++) {
    vis[i][0] = 0;
    sum[i][0] = 0;
    for (int j = 1; j <= k; j++) {
      vis[i][j] = vis[i][j - 1] + 1;
      sum[i][j] = sum[i][j - 1] + abs(i - c) + abs(j - c);
    }
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &m);
    solve(m);
  }
  return 0;
}
