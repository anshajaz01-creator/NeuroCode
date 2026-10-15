#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int dp[maxn][3][3];
void DJongmah(istream& cin, ostream& cout) {
  int n, m;
  cin >> n >> m;
  vector<int> al(m + 1);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    al[a]++;
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        for (int d = 0; d < 3; d++) {
          if (j + k + d > al[i]) continue;
          dp[i][k][d] =
              max(dp[i][k][d], dp[i - 1][j][k] + d + (al[i] - j - k - d) / 3);
        }
  }
  cout << dp[m][0][0] << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  std::istream& in(std::cin);
  std::ostream& out(std::cout);
  DJongmah(in, out);
  return 0;
}
