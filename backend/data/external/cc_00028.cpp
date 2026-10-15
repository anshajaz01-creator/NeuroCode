#include <bits/stdc++.h>
using namespace std;
int prvi[2000003];
int drugi[2000003];
int ind[1000001];
int main() {
  int n1, n2;
  scanf("%d%d", &n1, &n2);
  for (int i = 0; i < n1; i++) {
    scanf("%d", &prvi[i]);
    prvi[i + n1] = prvi[i];
  }
  for (int i = 0; i < n2; i++) {
    scanf("%d", &drugi[i]);
    drugi[i + n2] = drugi[i];
  }
  memset(ind, -1, sizeof(ind));
  for (int i = 0; i < n2; i++) {
    ind[drugi[i]] = i;
  }
  int p1 = 0;
  int p2 = 0;
  int naj = 0;
  int zadnji = -1;
  int len = 0;
  for (p1 = 0; p1 < n1; p1++) {
    while (p2 - p1 < n1) {
      if (ind[prvi[p2]] == -1) {
        break;
      }
      if (p1 == p2) {
        len = 1;
        p2++;
        continue;
      }
      int tren = ind[prvi[p2]] - ind[prvi[p2 - 1]];
      if (tren < 0) {
        tren += n2;
      }
      if (tren + len > n2) {
        break;
      }
      len += tren;
      p2++;
    }
    if (p2 - p1 > naj) {
      naj = p2 - p1;
    }
    if (p1 == p2) {
      p2++;
    }
    if (p2 - p1 > 1) {
      int prevec = ind[prvi[p1 + 1]] - ind[prvi[p1]];
      if (prevec < 0) {
        prevec += n2;
      }
      len -= prevec;
    }
  }
  cout << naj << "\n";
  return 0;
}
