#include <bits/stdc++.h>
using namespace std;
int dp[260][260];
int tdp[260][260];
void dpcopy() {
  for (int i = 'a'; i <= 'z'; i++)
    for (int j = 'a'; j <= 'z'; j++) tdp[i][j] = dp[i][j];
}
void pdcopy() {
  for (int i = 'a'; i <= 'z'; i++)
    for (int j = 'a'; j <= 'z'; j++) dp[i][j] = tdp[i][j];
}
int main() {
  int n;
  char temp[15];
  for (int i = 0; i < 260; i++)
    for (int j = 0; j < 260; j++) dp[i][j] = 0;
  scanf("%d", &n);
  while (n--) {
    scanf("%s", temp);
    int len = strlen(temp);
    int s = temp[0];
    int t = temp[len - 1];
    dpcopy();
    for (int i = 'a'; i <= 'z'; i++) {
      for (int j = 'a'; j <= 'z'; j++) {
        if (j == s && dp[i][j]) tdp[i][t] = max(dp[i][j] + len, tdp[i][t]);
      }
    }
    tdp[s][t] = max(tdp[s][t], len);
    pdcopy();
  }
  int ans = 0;
  for (int i = 'a'; i <= 'z'; i++) {
    if (dp[i][i] > ans) ans = dp[i][i];
  }
  printf("%d\n", ans);
}
