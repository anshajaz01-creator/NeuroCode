#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1024000;
const int MOD = 1000000007;
int add(int a, int b) { return a + b >= MOD ? a + b - MOD : a + b; }
int sub(int a, int b) { return a < b ? a - b + MOD : a - b; }
int mul(int a, int b) { return (long long)a * b % MOD; }
int n, m;
int dpB[MAXN], dpB0[MAXN], totB[MAXN];
int dpW[MAXN], dpW0[MAXN], totW[MAXN];
char s[MAXN];
void init(char goal, int *dp, int *dp0, int *tot) {
  int prevLength = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'X') {
      tot[i] = add(i ? tot[i - 1] : 1, i ? tot[i - 1] : 1);
    } else {
      tot[i] = i ? tot[i - 1] : 1;
    }
    int currLength = s[i] == 'X' || s[i] == goal ? prevLength + 1 : 0;
    if (currLength >= m && (i < m || s[i - m] != goal)) {
      dp0[i] = i <= m ? 1 : sub(tot[i - m - 1], dp[i - m - 1]);
    } else {
      dp0[i] = 0;
    }
    if (s[i] == 'X') {
      dp[i] = add(add(i ? dp[i - 1] : 0, i ? dp[i - 1] : 0), dp0[i]);
    } else {
      dp[i] = add(i ? dp[i - 1] : 0, dp0[i]);
    }
    prevLength = currLength;
  }
}
int calc() {
  int res = 0;
  for (int i = 1; i < n; i++) {
    res = add(res, mul(dpB[i - 1], dpW0[i]));
  }
  return res;
}
int main() {
  scanf("%d%d%s", &n, &m, s);
  init('B', dpB, dpB0, totB);
  reverse(s, s + n);
  init('W', dpW, dpW0, totW);
  reverse(dpW, dpW + n);
  reverse(dpW0, dpW0 + n);
  printf("%d\n", calc());
  return 0;
}
