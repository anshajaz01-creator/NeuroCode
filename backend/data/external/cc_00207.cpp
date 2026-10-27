#include <bits/stdc++.h>
using namespace std;
int counter[30][30];
char word[15];
int main() {
  int n, length;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", &word);
    length = strlen(word);
    for (int i = 0; i <= 'z' - 'a'; i++) {
      if (word[0] - 'a' == i || counter[i][word[0] - 'a']) {
        counter[i][word[length - 1] - 'a'] =
            max(counter[i][word[length - 1] - 'a'],
                counter[i][word[0] - 'a'] + length);
      }
    }
  }
  int result = 0;
  for (int i = 0; i <= 'z' - 'a'; i++) {
    result = max(result, counter[i][i]);
  }
  printf("%d\n", result);
  return 0;
}
