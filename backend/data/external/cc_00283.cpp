#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int maxm = 2e5 + 10;
const int inf = 0x3f3f3f3f;
int n;
vector<pair<int, int> > vec;
struct CUP {
  int v, pos;
} c[1010], d[1010];
bool cmp(CUP a, CUP b) { return a.v < b.v; }
int main() {
  ios_base::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> c[i].v;
    d[i].v = c[i].v;
    c[i].pos = i;
    d[i].pos = i;
  }
  sort(c + 1, c + 1 + n, cmp);
  int tmp;
  if (n & 1) {
    tmp = c[(1 + n) >> 1].v;
  } else {
    tmp = (c[(1 + n) >> 1].v + c[((1 + n) >> 1) + 1].v) >> 1;
  }
  int num = 0, cnt = 0;
  vec.clear();
  for (int l = 1, r = n; l <= r; l++, r--) {
    if (c[l].v != tmp) {
      num++;
    }
    if (c[r].v != tmp) {
      num++;
    }
    if (c[l].v + c[r].v == tmp * 2 && c[l].v != tmp && c[r].v != tmp) {
      cnt += 2;
      vec.push_back(pair<int, int>(c[r].pos, c[l].pos));
    }
  }
  if (num == 0) {
    cout << "Exemplary pages." << endl;
  } else {
    if (cnt != num || cnt > 2) {
      cout << "Unrecoverable configuration." << endl;
    } else {
      for (int i = 0; i < vec.size(); i++) {
        printf("%d ml. from cup #%d to cup #%d.\n",
               (d[vec[i].first].v - d[vec[i].second].v) >> 1, vec[i].second,
               vec[i].first);
      }
    }
  }
  return 0;
}
