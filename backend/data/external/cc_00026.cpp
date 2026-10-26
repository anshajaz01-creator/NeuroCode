#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:64000000")
using namespace std;
const int INF = (int)1E9;
const long long INF64 = (long long)1E18;
const long double EPS = 1E-9;
const long double PI = 3.1415926535897932384626433832795;
const int MAXN = 2001000;
int n1, n2, a1[MAXN], a2[MAXN], pos[MAXN];
int main() {
  cin >> n1 >> n2;
  for (int i = 0; i < (int)(n1); i++) {
    scanf("%d", &a1[i]);
    a1[n1 + i] = a1[i];
  }
  memset(pos, 255, sizeof pos);
  for (int i = 0; i < (int)(n2); i++) {
    scanf("%d", &a2[i]);
    a2[n2 + i] = a2[i];
    pos[a2[i]] = i;
  }
  int ans = 0, r = 0, last = -1, len = 0;
  for (int l = 0; l < (int)(n1); l++) {
    while (r - l < n1) {
      if (pos[a1[r]] == -1) break;
      if (r == l) {
        len = 1;
        r++;
      } else {
        int cur = (pos[a1[r]] - pos[a1[r - 1]] + n2) % n2;
        if (cur + len > n2) break;
        len += cur;
        r++;
      }
    }
    ans = max(ans, r - l);
    if (r == l)
      r++;
    else if (r - l > 1)
      len -= (pos[a1[l + 1]] - pos[a1[l]] + n2) % n2;
  }
  cout << ans << endl;
  return 0;
}
