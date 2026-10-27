#include <bits/stdc++.h>
using namespace std;
void initialize();
void find_xyz();
void display();
long n;
vector<string> a, b;
vector<bool> used;
vector<int> sz;
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  initialize();
  find_xyz();
  display();
  return 0;
}
void initialize() {
  cin >> n;
  int s;
  sz.resize(1000);
  a.resize(n);
  for (int i = 0; i <= n - 1; i++) {
    s = 0;
    cin >> a[i];
    for (int j = 0; j <= a[i].size() - 1; j++) s += a[i][j];
    sz[s]++;
  }
  b.resize(n);
  for (int i = 0; i <= n - 1; i++) cin >> b[i];
}
void find_xyz() {
  int s = 0, ans = 0;
  ;
  for (int i = 0; i <= n - 1; i++) {
    s = 0;
    for (int j = 0; j <= b[i].size() - 1; j++) s += b[i][j];
    if (sz[s] > 0)
      sz[s]--;
    else
      ans++;
  }
  cout << ans;
}
void display() {}
