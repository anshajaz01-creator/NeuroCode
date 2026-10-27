#include <bits/stdc++.h>
using namespace std;
int ceil_div(int a, int b) { return (a / b * b == a ? a / b : a / b + 1); }
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, cl, ce, v;
  cin >> n >> m >> cl >> ce >> v;
  vector<int> stairs;
  vector<int> elev;
  if (cl) {
    for (int i = 0; i < cl; ++i) {
      int a;
      cin >> a;
      stairs.push_back(a);
    }
  }
  if (ce) {
    for (int i = 0; i < ce; ++i) {
      int a;
      cin >> a;
      elev.push_back(a);
    }
  }
  int q;
  cin >> q;
  while (q--) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    if (a == x) {
      cout << abs(b - y) << endl;
      continue;
    }
    int stairs_dist = 1e9;
    if (cl) {
      auto b_s = lower_bound(stairs.begin(), stairs.end(), b);
      auto y_s = lower_bound(stairs.begin(), stairs.end(), y);
      if (b_s != y_s) {
        stairs_dist = abs(x - a) + abs(y - b);
      } else {
        if (b_s == stairs.end()) {
          --b_s;
          stairs_dist = abs(x - a) + abs(b - *b_s) + abs(y - *b_s);
        } else {
          stairs_dist = abs(x - a) + abs(b - *b_s) + abs(y - *b_s);
          if (b_s != stairs.begin()) {
            --b_s;
            stairs_dist =
                min(stairs_dist, abs(x - a) + abs(b - *b_s) + abs(y - *b_s));
          }
        }
      }
    }
    int lift_dist = 1e9;
    if (ce) {
      auto b_l = lower_bound(elev.begin(), elev.end(), b);
      auto y_l = lower_bound(elev.begin(), elev.end(), y);
      if (b_l != y_l) {
        lift_dist = ceil_div(abs(x - a), v) + abs(y - b);
      } else {
        if (b_l == elev.end()) {
          --b_l;
          lift_dist = ceil_div(abs(x - a), v) + abs(b - *b_l) + abs(y - *b_l);
        } else {
          lift_dist = ceil_div(abs(x - a), v) + abs(b - *b_l) + abs(y - *b_l);
          if (b_l != elev.begin()) {
            --b_l;
            lift_dist = min(lift_dist, ceil_div(abs(x - a), v) + abs(b - *b_l) +
                                           abs(y - *b_l));
          }
        }
      }
    }
    cout << min(lift_dist, stairs_dist) << endl;
  }
}
