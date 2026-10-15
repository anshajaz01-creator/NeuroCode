#include <bits/stdc++.h>
const int N = 200000;
struct edge {
  int to, next;
} e[2 * N];
int n, m, head[N], cnt = 0;
int a[N], b[N], ca, cb;
int color[N];
std::queue<int> Q;
int main() {
  scanf("%d%d", &n, &m);
  int x, y;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &x, &y);
    e[++cnt].to = y;
    e[cnt].next = head[x];
    head[x] = cnt;
    e[++cnt].to = x;
    e[cnt].next = head[y];
    head[y] = cnt;
  }
  while (!Q.empty()) Q.pop();
  for (int i = 1; i <= n; i++)
    if (!color[i]) {
      if (head[i] != 0) a[++ca] = i;
      color[i] = 1;
      Q.push(i);
      while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; i; i = e[i].next) {
          if (!color[e[i].to]) {
            if (color[x] == 1) {
              color[e[i].to] = 2;
              b[++cb] = e[i].to;
              Q.push(e[i].to);
            } else {
              color[e[i].to] = 1;
              a[++ca] = e[i].to;
              Q.push(e[i].to);
            }
          } else {
            if (color[x] == color[e[i].to]) {
              printf("-1\n");
              return 0;
            }
          }
        }
      }
    }
  printf("%d\n", ca);
  for (int i = 1; i <= ca; i++) printf("%d ", a[i]);
  printf("\n");
  printf("%d\n", cb);
  for (int i = 1; i <= cb; i++) printf("%d ", b[i]);
  printf("\n");
  return 0;
}
