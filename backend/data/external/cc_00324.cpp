#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
char num[N];
int ans[N];
int main() {
  int n, m;
  scanf("%d", &n);
  scanf("%s", (num + 1));
  int r = 0, b = 0;
  for (int i = 1; i <= n; i++) {
    if (i & 1) {
      if (num[i] != 'r') {
        b++;
      }
    } else {
      if (num[i] != 'b') {
        r++;
      }
    }
  }
  int all = min(r, b) + abs(r - b);
  r = b = 0;
  for (int i = 1; i <= n; i++) {
    if (i & 1) {
      if (num[i] != 'b') {
        r++;
      }
    } else {
      if (num[i] != 'r') {
        b++;
      }
    }
  }
  cout << min(all, min(r, b) + abs(r - b)) << endl;
  return 0;
}
