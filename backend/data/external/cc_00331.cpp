#include <bits/stdc++.h>
using namespace std;
const int N = 100;
char d[100][100];
bool row[N], col[N];
int n, m;
void mark(int r) {
  vector<int> ind;
  for (int i = 0; i < m; ++i) {
    if (d[r][i] == '#') {
      ind.push_back(i);
    }
  }
  for (int i = 0; i < n; ++i) {
    bool was = 0;
    for (int j : ind) {
      if (d[i][j] == '#') {
        was = 1;
        if (row[i]) {
          cout << "No\n";
          exit(0);
        }
      }
    }
    if (was) {
      row[i] = 1;
      for (int j : ind) {
        if (d[i][j] == '.') {
          cout << "No\n";
          exit(0);
        } else {
          d[i][j] = '.';
        }
      }
    }
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> d[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (d[i][j] == '#') {
        mark(i);
      }
    }
  }
  cout << "Yes\n";
  return 0;
}
