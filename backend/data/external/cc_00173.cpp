#include <bits/stdc++.h>
using namespace std;
const int SIZE = 1100;
char A[SIZE], S[2 * SIZE];
int N;
int main() {
  int r = 1000 * 1000 * 1000;
  cin >> N >> A;
  strcat(S, A);
  strcat(S, A);
  for (int i = 0; i != N; i++) {
    int a = 0, b = 0, d;
    for (int j = i; j != i + N; j++)
      if (S[j] == 'H')
        a++;
      else
        b++;
    d = 0;
    for (int j = i; j != i + a; j++)
      if (S[j] != 'H') d++;
    if (r > d) r = d;
    d = 0;
    for (int j = i; j != i + b; j++)
      if (S[j] != 'T') d++;
    if (r > d) r = d;
  }
  cout << r;
  return 0;
}
