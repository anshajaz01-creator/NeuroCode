#include <bits/stdc++.h>
using namespace std;
typedef int def;
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
  if (!v.empty()) {
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
  }
  return out;
}
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& v) {
  if (!v.empty()) {
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
  }
  return out;
}
const int N = 1e6 + 10;
const long long M = 1e9 + 7;
int Am[N][25], A[N];
bool isLegal(int g, int i, int j, int k) {
  return A[g - 2] >= i + k && A[g - 1] >= j + k && A[g] >= k;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  for (def i = 0; i < (n); i++) {
    int tp;
    cin >> tp;
    A[tp]++;
  }
  for (def i = 1; i <= (m); i++) {
    for (def j = 0; j < (25); j++) Am[i][j] = -1;
  }
  if (m == 1) {
    cout << A[1] / 3;
    exit(0);
  }
  Am[1][0] = Am[2][0] = 0;
  for (def g = (3); g < (m + 1); g++) {
    for (def i = 0; i < (5); i++) {
      for (def j = 0; j < (3); j++) {
        for (def k = 0; k < (3); k++) {
          if (isLegal(g, i, j, k) && Am[g - 1][i * 3 + j] != -1)
            Am[g][(j + k) * 3 + k] =
                max(Am[g][(j + k) * 3 + k],
                    k + Am[g - 1][i * 3 + j] + (A[g - 2] - i - k) / 3);
        }
      }
    }
  }
  int ans = 0;
  for (def i = 0; i < (5); i++) {
    for (def j = 0; j < (3); j++) {
      if (Am[m][i * 3 + j] != -1)
        ans = max(ans, Am[m][i * 3 + j] + (A[m - 1] - i) / 3 + (A[m] - j) / 3);
    }
  }
  cout << ans;
}
