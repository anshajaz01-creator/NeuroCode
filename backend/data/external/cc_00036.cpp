#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
int n, m;
bool mark[MAXN];
vector<int> adj[MAXN];
vector<int> boom[MAXN];
bool DFS(int cur, int p) {
  mark[cur] = true;
  for (int i = 0; i < (int)adj[cur].size(); i++) {
    int viz = adj[cur][i];
    if (mark[viz]) {
      if (viz != p) boom[viz].push_back(cur);
      continue;
    }
    if (!DFS(viz, cur)) boom[cur].push_back(viz);
  }
  while ((int)boom[cur].size() > 1) {
    int A = boom[cur].back();
    boom[cur].pop_back();
    int B = boom[cur].back();
    boom[cur].pop_back();
    printf("%d %d %d\n", A, cur, B);
  }
  if (boom[cur].empty()) return false;
  printf("%d %d %d\n", p, cur, boom[cur].back());
  return true;
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int U, V;
    scanf("%d %d", &U, &V);
    adj[U].push_back(V);
    adj[V].push_back(U);
  }
  if (m % 2 == 1) {
    printf("No solution\n");
    return 0;
  }
  DFS(1, 1);
}
