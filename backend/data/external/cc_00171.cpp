#include <bits/stdc++.h>
using namespace std;
long long int const mod = 1e9 + 7;
long long int const inf = 1e15 + 7;
long long int const mxn = 2e5 + 1;
inline void file() {}
long long int k, n, m;
string s[mxn];
bool ch(long long int i, long long int j) {
  return (i >= 0 && i < n && j >= 0 && j < m && s[i][j] == '.');
}
void dfs(long long int i, long long int j) {
  if (k > 0) {
    s[i][j] = 'X';
    k--;
  } else
    s[i][j] = '!';
  if (ch(i + 1, j)) dfs(i + 1, j);
  if (ch(i - 1, j)) dfs(i - 1, j);
  if (ch(i, j + 1)) dfs(i, j + 1);
  if (ch(i, j - 1)) dfs(i, j - 1);
}
int main() {
  file();
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  {
    long long int c = 0;
    cin >> n >> m >> k;
    for (long long int i = 0; i < n; i++) cin >> s[i];
    for (long long int i = 0; i < n; i++) {
      for (long long int j = 0; j < m; j++) {
        if (s[i][j] == '.') c++;
      }
    }
    k = c - k;
    for (long long int i = 0; i < n; i++) {
      for (long long int j = 0; j < m; j++) {
        if (s[i][j] == '.') dfs(i, j);
      }
    }
    for (long long int i = 0; i < n; i++) {
      for (long long int j = 0; j < m; j++) {
        if (s[i][j] == '!')
          s[i][j] = 'X';
        else if (s[i][j] == 'X')
          s[i][j] = '.';
      }
    }
    for (long long int i = 0; i < n; i++) cout << s[i] << "\n";
  }
}
