#include <bits/stdc++.h>
using namespace std;
const int MAX = 100010;
int P[MAX];
vector<int> E[MAX];
map<pair<int, int>, int> M;
int L = -1;
void dfs(int x) {
  for (int y : E[x]) {
    if (P[y] == 0) {
      P[y] = x;
      dfs(y);
      return;
    }
  }
  L = x;
}
int main() {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  while (m--) {
    int a, b;
    scanf("%d %d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
    M[pair<int, int>(a, b)] = 1;
    M[pair<int, int>(b, a)] = 1;
  }
  P[1] = -1;
  dfs(1);
  int length = 1, v = L;
  while (true) {
    v = P[v];
    length++;
    if (length > k && M[pair<int, int>(v, L)]) {
      printf("%d\n", length);
      for (int x = L; x != v; x = P[x]) {
        printf("%d ", x);
      }
      printf("%d\n", v);
      return (0);
    }
  }
}
