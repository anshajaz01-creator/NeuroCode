#include <bits/stdc++.h>
using namespace std;
const int maxn = 211111;
int a[maxn], n;
int nowStart;
int el[maxn], p[maxn], len;
long long nowD;
void newArift(int st) {
  nowStart = st;
  len = 0;
}
bool tryAdd(int pos, int x) {
  if (len == 0) {
    if (x == -1) return true;
    el[len] = x, p[len] = pos;
    len++;
    return true;
  } else if (len == 1) {
    if (x == -1) {
      return true;
    } else {
      if ((x - el[0]) % (pos - p[0]) == 0) {
        long long d = (x - el[0]) / (pos - p[0]);
        long long frst = (nowStart - pos) * d + x;
        if (frst >= 1) {
          el[len] = x, p[len] = pos;
          len++;
          nowD = d;
          return true;
        } else
          return false;
      } else
        return false;
    }
  } else {
    if (x == -1) {
      long long now = nowD * (pos - p[0]) + el[0];
      if (now >= 1) return true;
      return false;
    }
    if ((x - el[0]) % (pos - p[0]) == 0) {
      long long d = (x - el[0]) / (pos - p[0]);
      if (d != nowD) return false;
      el[len] = x, p[len] = pos;
      len++;
      return true;
    } else
      return false;
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  int st = 1;
  int z = 0;
  while (st <= n) {
    newArift(st);
    int r = st;
    while (r <= n) {
      if (tryAdd(r, a[r])) {
        r++;
      } else
        break;
    }
    st = r;
    z++;
  }
  cout << z << '\n';
  return 0;
}
