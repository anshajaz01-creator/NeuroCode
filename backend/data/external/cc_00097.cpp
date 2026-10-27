#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k;
  cin >> n >> k;
  vector<int> v, u;
  unordered_map<int, int> m;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    if (m.find(a) == m.end()) {
      v.push_back(a);
    }
    m[a]++;
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < k; i++) {
    int a;
    cin >> a;
    u.push_back(a);
  }
  for (int i = 0; i < k; i++) {
    int x = u[i];
    int y = 0;
    for (int j = v.size() - 1; j >= 0; j--) {
      int a = v[j];
      int b = m[a];
      if (x >= a) {
        int c = x / a;
        if (c <= b) {
          x = x - c * a;
          y = y + c;
        } else {
          x = x - b * a;
          y = y + b;
        }
      }
    }
    if (x == 0) {
      cout << y << endl;
    } else {
      cout << -1 << endl;
    }
  }
}
