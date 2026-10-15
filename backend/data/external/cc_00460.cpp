#include <bits/stdc++.h>
using namespace std;
template <class A, class B>
inline bool mina(A &first, B second) {
  return (first > second) ? (first = second, 1) : 0;
}
template <class A, class B>
inline bool maxa(A &first, B second) {
  return (first < second) ? (first = second, 1) : 0;
}
const int MAXN = 1000005;
int N, M;
int in[MAXN];
int dp[MAXN][3][3];
int main() {
  cin >> N >> M;
  int a;
  for (int i = 0; (i) < (N); ++(i)) {
    cin >> a;
    in[a]++;
  }
  memset(dp, -(0x3f3f3f3f), sizeof(dp));
  for (int i = 1; i <= M; i++) {
    for (int two = 0; two < 3; two++) {
      for (int one = 0; one < 3; one++) {
        if (in[i - 1] < two || in[i] < two + one) continue;
        int a = (in[i] - two - one) / 3;
        int maxx = 0;
        for (int p = 0; (p) < (3); ++(p))
          for (int q = 0; (q) < (3); ++(q)) {
            if (p + q >= two) maxa(maxx, dp[i - 1][p][q]);
          }
        dp[i][two][one] = a + maxx;
        for (int hor = 1; hor < 3; hor++) {
          if (in[i] - two - one - hor >= 0) {
            int a = (in[i] - two - one - hor) / 3 + hor;
            for (int p = 0; (p) < (3); ++(p))
              for (int q = 0; (q) < (3); ++(q)) {
                if (p >= hor && p + q - hor >= two) {
                  maxa(dp[i][two][one], a + dp[i - 1][p][q]);
                }
              }
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; (i) < (M + 1); ++(i)) {
    for (int p = 0; (p) < (3); ++(p)) {
      for (int q = 0; (q) < (3); ++(q)) {
        maxa(ans, dp[i][p][q]);
      }
    }
  }
  cout << ans << endl;
  return 0;
}
