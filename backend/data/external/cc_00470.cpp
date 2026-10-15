#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> v;
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    v.push_back(make_pair(x, 0));
  }
  sort(v.begin(), v.end());
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    int ok = 0;
    for (int j = i + 1; j < n; j++) {
      if (v[i].first < v[j].first && v[j].second == 0) {
        ok = 1;
        v[j].second = 1;
        break;
      }
    }
    if (!ok) {
      cnt++;
    }
  }
  printf("%d", cnt);
  return 0;
}
