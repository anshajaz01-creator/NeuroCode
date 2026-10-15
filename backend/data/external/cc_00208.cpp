#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  int dp[26][26] = {};
  while (n--) {
    char s[15];
    scanf("%s", s);
    int len = strlen(s);
    int a = s[0] - 'a';
    int b = s[len - 1] - 'a';
    for (int i = 0; i < 26; i++) {
      if (dp[i][a] == 0) continue;
      dp[i][b] = max(dp[i][b], dp[i][a] + len);
    }
    dp[a][b] = max(dp[a][b], len);
  }
  int ans = 0;
  for (int i = 0; i < 26; i++) ans = max(ans, dp[i][i]);
  printf("%d\n", ans);
  return 0;
}
