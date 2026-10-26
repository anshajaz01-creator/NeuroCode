#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > g;
bool isans;
int was[100100];
vector<int> st;
int n, m, k;
void dfs(int v, int p) {
  if (isans) return;
  if (was[v] == 2) return;
  if (was[v] == 1) {
    int p1 = -1;
    for (int i = (0); i < (st.size()); ++i)
      if (st[i] == v) p1 = i;
    if (st.size() - p1 > k) {
      printf("%d\n", st.size() - p1);
      for (int i = (p1); i < (st.size()); ++i) {
        if (i != p1) printf(" ");
        printf("%d", st[i] + 1);
      }
      printf("\n");
      isans = true;
      return;
    }
    return;
  }
  was[v] = 1;
  st.push_back(v);
  for (int i = (0); i < (g[v].size()); ++i) {
    if (isans) return;
    if (g[v][i] == p) continue;
    dfs(g[v][i], v);
  }
  st.pop_back();
  was[v] = 2;
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  g.resize(n);
  for (int i = (0); i < (m); ++i) {
    int v1, v2;
    scanf("%d%d", &v1, &v2);
    g[v1 - 1].push_back(v2 - 1);
    g[v2 - 1].push_back(v1 - 1);
  }
  isans = false;
  for (int i = (0); i < (n); ++i)
    if ((was[i] == 0)) dfs(i, -1);
  if (isans == false) {
    int k = 1;
    int c = 0;
    while (1) c += k;
  }
  return 0;
}
