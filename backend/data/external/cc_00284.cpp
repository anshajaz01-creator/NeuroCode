#include <bits/stdc++.h>
using namespace std;
bool compare(vector<int> a, vector<int> b) { return a[0] < b[0]; }
int main() {
  int n;
  cin >> n;
  if (n == 1) {
    int x;
    cin >> x;
    cout << "Exemplary pages.";
    return 0;
  } else if (n == 2) {
    int x, y;
    cin >> x >> y;
    if (x == y)
      cout << "Exemplary pages.";
    else if ((x + y) % 2 != 0)
      cout << "Unrecoverable configuration.";
    else if (x > y)
      cout << x - (x + y) / 2 << " ml. from cup #2 to cup #1.";
    else
      cout << y - (x + y) / 2 << " ml. from cup #1 to cup #2.";
    return 0;
  }
  vector<vector<int>> v;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    vector<int> v1;
    v1.push_back(x);
    v1.push_back(i + 1);
    v.push_back(v1);
  }
  sort(v.begin(), v.end(), compare);
  if (v[0][0] == v[n - 1][0])
    cout << "Exemplary pages.";
  else {
    for (int i = 1; i < n - 1; i++) {
      if (v[i][0] != v[1][0]) {
        cout << "Unrecoverable configuration.";
        return 0;
      }
    }
    if (v[1][0] - v[0][0] != v[n - 1][0] - v[1][0]) {
      cout << "Unrecoverable configuration.";
      return 0;
    }
    cout << v[1][0] - v[0][0] << " ml. from cup #" << v[0][1] << " to cup #"
         << v[n - 1][1] << ".";
  }
}
