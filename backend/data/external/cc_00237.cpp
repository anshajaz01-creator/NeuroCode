#include <bits/stdc++.h>
using namespace std;
char B[1 << 20];
char W[1 << 20];
long long RB[1 << 20];
long long RW[1 << 20];
long long Two[1 << 20];
long long CX[1 << 20];
long long CB[1 << 20];
void F(int n, int k, char B[], long long R[], char c) {
  int i;
  CX[0] = 0;
  CB[0] = 0;
  for (i = (0); i < (n); ++i) {
    CX[i + 1] = CX[i];
    CB[i + 1] = CB[i];
    if (B[i] == c) ++CB[i + 1];
    if (B[i] == 'X') ++CX[i + 1];
  }
  long long sum = 0;
  long long sum2 = 0;
  for (i = (0); i < (n); ++i) {
    R[i] = 0;
    if (i + 1 < k) continue;
    long long cx = CX[i + 1] - CX[i + 1 - k];
    long long cb = CB[i + 1] - CB[i + 1 - k];
    if (cx + cb == k)
      R[i] = (Two[CX[i + 1 - k]] + 1000000007 - sum + 1000000007 - sum2) %
             1000000007;
    sum += R[i];
    sum += 1000000007 - R[i + 1 - k];
    sum %= 1000000007;
    if (B[i + 1 - k] == 'X') sum2 += sum2;
    sum2 += R[i + 1 - k];
    sum2 %= 1000000007;
  }
}
int main() {
  int n, k;
  scanf("%d%d%s", &n, &k, B);
  int i;
  for (i = (0); i < (n); ++i) W[i] = B[i];
  Two[0] = 1;
  for (i = (0); i < (n); ++i) Two[i + 1] = (Two[i] + Two[i]) % 1000000007;
  reverse(W, W + n);
  F(n, k, B, RB, 'B');
  F(n, k, W, RW, 'W');
  long long res = 0;
  long long sum = 0;
  for (i = (n)-1; i >= (0); --i) {
    res += RB[i] * sum % 1000000007;
    if (B[i] == 'X') sum += sum;
    sum += RW[n - 1 - i];
    sum %= 1000000007;
  }
  printf("%d\n", int(res % 1000000007));
  return 0;
};
