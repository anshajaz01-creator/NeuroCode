#include <bits/stdc++.h>
using namespace std;
struct point {
  int x, y;
};
bool cmp(struct point& a, struct point& b) {
  if (a.y == b.y)
    return a.x < b.x;
  else
    return a.y < b.y;
}
char ans[1000000];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    memset(ans, 0, sizeof(ans));
    bool isOK = true;
    point p[1010];
    int n, cnt = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1, cmp);
    int lasty = 0, lastx = 0, maxx = 0;
    for (int i = 1; i <= n; ++i) {
      int temp;
      if (p[i].y == lasty) {
        temp = p[i].x - lastx;
        while (temp--) ans[cnt++] = 'R';
        maxx = max(p[i].x, maxx);
        lasty = p[i].y;
        lastx = p[i].x;
      } else {
        if (p[i].x < maxx) {
          isOK = false;
          break;
        }
        temp = p[i].y - lasty;
        int temp2 = p[i].x - lastx;
        while (temp2--) ans[cnt++] = 'R';
        while (temp--) ans[cnt++] = 'U';
        maxx = max(p[i].x, maxx);
        lastx = p[i].x;
        lasty = p[i].y;
      }
    }
    if (isOK) {
      printf("YES\n");
      printf("%s\n", ans);
    } else
      printf("NO\n");
  }
  return 0;
}
