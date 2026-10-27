#include <bits/stdc++.h>
using namespace std;
char a[10010];
char b[10010], c[1010], d[1010];
int main() {
  while (scanf("%s%s", a, b) != EOF) {
    int len = strlen(a);
    sort(a, a + len);
    int flag = 0;
    for (int i = 0; i < len; i++) {
      if (a[i] != '0') {
        flag = i;
        char t = a[i];
        a[i] = a[0];
        a[0] = t;
        break;
      }
    }
    if (strcmp(a, b) == 0) {
      printf("OK\n");
    } else {
      printf("WRONG_ANSWER\n");
    }
  }
  return 0;
}
