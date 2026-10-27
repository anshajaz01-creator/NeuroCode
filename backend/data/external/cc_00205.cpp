#include <bits/stdc++.h>
using namespace std;
int res[2][10], nov[2][10], fix[2];
inline int min(int a, int b) { return a < b ? a : b; }
int decPair(int a[], int b[]) {
  for (int i = 1; i <= 9; i++)
    if (a[i] && b[10 - i]) return i;
  return 0;
}
int main() {
  memset(res, 0, sizeof(res));
  for (char c = getchar(); c != '\n'; c = getchar()) {
    res[0][c - '0']++;
    res[1][c - '0']++;
  }
  memset(nov, 0, sizeof(nov));
  fix[0] = fix[1] = 0;
  if (decPair(res[0], res[1])) {
    for (int i = 0; i <= 9; i++)
      nov[0][i] = nov[1][9 - i] = min(res[0][i], res[1][9 - i]);
    for (int i = 0; i <= 9; i++) {
      res[0][i] -= nov[0][i];
      res[1][i] -= nov[1][i];
    }
    if (fix[0] = decPair(res[0], res[1])) {
      fix[1] = 10 - fix[0];
      res[0][fix[0]]--;
      res[1][fix[1]]--;
    } else if (fix[0] = decPair(res[0], nov[1])) {
      fix[1] = 10 - fix[0];
      res[0][fix[0]]--;
      nov[1][fix[1]]--;
      nov[0][9 - fix[1]]--;
      res[0][9 - fix[1]]++;
    } else if (fix[0] = decPair(nov[0], res[1])) {
      fix[1] = 10 - fix[0];
      nov[0][fix[0]]--;
      nov[1][9 - fix[0]]--;
      res[1][9 - fix[0]]++;
      res[1][fix[1]]--;
    } else if (fix[0] = decPair(nov[0], nov[1])) {
      fix[1] = 10 - fix[0];
      nov[0][fix[0]]--;
      nov[1][9 - fix[0]]--;
      res[1][9 - fix[0]]++;
      nov[1][fix[1]]--;
      nov[0][9 - fix[1]]--;
      res[0][9 - fix[1]]++;
    }
  }
  int zero = min(res[0][0], res[1][0]);
  res[0][0] -= zero;
  res[1][0] -= zero;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j <= 9; j++)
      for (int k = 1; k <= res[i][j]; k++) putchar('0' + j);
    for (int j = 0; j <= 9; j++)
      for (int k = 1; k <= nov[i][i ? 9 - j : j]; k++)
        putchar('0' + (i ? 9 - j : j));
    if (fix[i]) putchar('0' + fix[i]);
    for (int k = 1; k <= zero; k++) putchar('0');
    putchar('\n');
  }
  return 0;
}
