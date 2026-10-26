#include <bits/stdc++.h>
using namespace std;
int main() {
  unsigned int N;
  char cstr[2005];
  scanf("%u%s", &N, cstr);
  strncat(cstr, cstr, N);
  unsigned int k, i, j;
  unsigned int nT = 0, nH = 0;
  for (k = 0; k < N; k++) {
    if (cstr[k] == 'T')
      nT++;
    else
      nH++;
  }
  bool b = (nH < nT);
  unsigned int m = b ? nH : nT;
  char cm = b ? 'H' : 'T';
  unsigned int mt = 0;
  for (k = 0; k < N; k++) {
    unsigned int t = 0;
    for (i = k; i < k + m; i++)
      if (cstr[i] == cm) t++;
    if (t > mt) mt = t;
  }
  printf("%u\n", m - mt);
  return 0;
}
