#include <bits/stdc++.h>
using namespace std;
const int N = 55;
int n, m;
int used[N][N];
int di[] = {0, 1, 0, -1};
int dj[] = {1, 0, -1, 0};
char f[N][N];
char nf[N][N];
vector<int> compi[N];
vector<int> compj[N];
bool ins(int i, int j) { return 0 <= i && i < n && 0 <= j && j < m; }
void dfs(int I, int J, int cn) {
  compi[cn].push_back(I);
  compj[cn].push_back(J);
  used[I][J] = 1;
  for (int d = 0; d < 4; d++) {
    int i = I + di[d];
    int j = J + dj[d];
    while (ins(i, j)) {
      if (f[i][j] == '#' && !used[i][j]) {
        dfs(i, j, cn);
        break;
      }
      i += di[d];
      j += dj[d];
    }
  }
}
int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      f[i][j] = s[j];
      nf[i][j] = '.';
    }
  }
  int cn = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (f[i][j] == '#' && !used[i][j]) {
        dfs(i, j, cn);
        cn++;
      }
    }
  }
  for (int k = 0; k < cn; k++) {
    for (int i : compi[k]) {
      for (int j : compj[k]) {
        nf[i][j] = '#';
      }
    }
  }
  int eq = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (nf[i][j] != f[i][j]) {
        eq = 0;
      }
    }
  }
  if (eq)
    cout << "Yes\n";
  else
    cout << "No\n";
  return 0;
}
