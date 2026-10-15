#include <bits/stdc++.h>
using namespace std;
const int NMAX = 100000 + 5;
int N, M, S;
set<int> V[NMAX];
bool Viz[NMAX];
void DFS(int nod, int tata) {
  set<int>::iterator it;
  set<int> W = V[nod];
  Viz[nod] = 1;
  for (it = W.begin(); it != W.end(); it++) {
    if (Viz[*it]) continue;
    DFS(*it, nod);
  }
  if (V[nod].size() % 2) V[nod].erase(tata);
  for (it = V[nod].begin(); it != V[nod].end(); it++) {
    printf("%d %d ", *it, nod);
    V[*it].erase(nod);
    it++;
    printf("%d\n", *it);
    V[*it].erase(nod);
  }
}
int main() {
  int x, y;
  scanf("%d%d", &N, &M);
  if (M % 2) {
    printf("No solution\n");
    return 0;
  }
  for (; M; --M) {
    scanf("%d%d", &x, &y);
    V[x].insert(y);
    V[y].insert(x);
  }
  DFS(1, 0);
  return 0;
}
