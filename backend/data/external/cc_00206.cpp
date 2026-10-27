#include <bits/stdc++.h>
using namespace std;
int countbit(int n) { return (n == 0) ? 0 : (1 + countbit(n & (n - 1))); }
int lowbit(int n) { return (n ^ (n - 1)) & n; }
const double pi = acos(-1.0);
const double eps = 1e-11;
template <class T>
T sqr(T x) {
  return x * x;
}
int N;
char str[100010];
vector<pair<int, int> > temp1, temp2, ans1, ans2;
int ans0;
int num[10];
int maxS;
int main() {
  scanf("%s", str);
  N = strlen(str);
  for (int i = 0; i < N; ++i) num[str[i] - '0']++;
  maxS = -1;
  for (int last = 1; last <= 9; ++last) {
    int tn1[10], tn2[10];
    memcpy(tn2, num, 40);
    memcpy(tn1, num, 40);
    temp1.clear();
    temp2.clear();
    int sum0 = 0;
    if (tn1[last] && tn2[10 - last]) {
      --tn1[last], --tn2[10 - last];
      temp1.push_back(make_pair(last, 1));
      temp2.push_back(make_pair(10 - last, 1));
      ++sum0;
      for (int i = 0; i < 10; ++i) {
        int t = min(tn1[i], tn2[9 - i]);
        tn1[i] -= t, tn2[9 - i] -= t;
        temp1.push_back(make_pair(i, t));
        temp2.push_back(make_pair(9 - i, t));
        sum0 += t;
      }
    }
    int t = min(tn1[0], tn2[0]);
    sum0 += t;
    tn1[0] -= t, tn2[0] -= t;
    for (int i = 0; i < 10; ++i) {
      if (tn1[i]) temp1.push_back(make_pair(i, tn1[i]));
      if (tn2[i]) temp2.push_back(make_pair(i, tn2[i]));
    }
    if (sum0 > maxS) {
      ans1 = temp1;
      ans2 = temp2;
      maxS = sum0;
      ans0 = t;
    }
  }
  if (maxS == -1) {
    printf("%s\n%s\n", str, str);
    return 0;
  }
  for (int i = ans1.size() - 1; i >= 0; --i) {
    int n = ans1[i].second;
    for (int j = 0; j < n; ++j) printf("%d", ans1[i].first);
  }
  for (int i = 0; i < ans0; ++i) printf("0");
  printf("\n");
  for (int i = ans2.size() - 1; i >= 0; --i) {
    int n = ans2[i].second;
    for (int j = 0; j < n; ++j) printf("%d", ans2[i].first);
  }
  for (int i = 0; i < ans0; ++i) printf("0");
  printf("\n");
  return 0;
}
