#include <bits/stdc++.h>
using namespace std;
const int maxn = 50000 * 25 + 10;
vector<int> a, f, s;
int n;
bitset<maxn> dp[52][26];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= 2 * n; ++i) {
    int x;
    scanf("%d", &x);
    a.push_back(x);
  }
  sort(a.begin(), a.end(), greater<int>());
  f.push_back(a.back()), a.pop_back();
  s.push_back(a.back()), a.pop_back();
  int sum = accumulate(a.begin(), a.end(), 0);
  dp[0][0][0] = 1;
  for (int i = 0; i < (int)a.size(); ++i) {
    dp[i + 1][0][0] = 1;
    for (int cho = 0; cho <= n - 1 && cho <= i; ++cho) {
      dp[i + 1][cho + 1] = dp[i][cho + 1] | (dp[i][cho] << (a[i]));
    }
  }
  int cur = sum / 2, ct = n - 1;
  while (!dp[a.size()][ct][cur]) cur--;
  for (int p = a.size() - 1; p >= 0; --p) {
    if (dp[p][ct][cur])
      f.push_back(a[p]);
    else {
      assert(dp[p][ct - 1][cur - a[p]]);
      s.push_back(a[p]);
      cur -= a[p], ct--;
    }
  }
  sort(f.begin(), f.end());
  sort(s.begin(), s.end(), greater<int>());
  for (int i = 0; i < n; ++i) printf("%d%c", f[i], " \n"[i == n - 1]);
  for (int i = 0; i < n; ++i) printf("%d%c", s[i], " \n"[i == n - 1]);
  return 0;
}
