#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
int n, m;
int fa[N + 3], deg[N + 3], ans[N + 3];
vector<pair<long long, int> > G[N + 3];
vector<int> cnt[N + 3];
void Merge(vector<int> &A, vector<int> &B) {
  if (A.size() < B.size()) swap(A, B);
  for (int i = 1; i <= B.size(); i++) A[A.size() - i] += B[B.size() - i];
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &fa[i]);
    deg[fa[i]]++;
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    long long x;
    int y;
    scanf("%lld%d", &x, &y);
    G[y].push_back(make_pair(x, i));
  }
  queue<int> Q;
  for (int i = 1; i <= n; i++) {
    if (!deg[i]) Q.push(i);
    cnt[i].push_back(1);
  }
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int i = 0; i < (int)G[u].size(); i++) {
      pair<long long, int> now = G[u][i];
      if (now.first >= (int)cnt[u].size())
        ans[now.second] = 0;
      else
        ans[now.second] = cnt[u][cnt[u].size() - 1 - now.first];
    }
    cnt[u].push_back(0);
    Merge(cnt[fa[u]], cnt[u]);
    deg[fa[u]]--;
    if (!deg[fa[u]]) Q.push(fa[u]);
  }
  for (int u = 1; u <= n; u++)
    if (deg[u]) {
      int cop = u, siz = 0;
      vector<int> cir;
      do {
        deg[cop] = 0;
        vector<int> cpy = cnt[cop];
        Merge(cir, cpy);
        siz++;
        cir.push_back(0);
        cop = fa[cop];
      } while (cop != u);
      for (int i = 1; i + siz <= cir.size(); i++)
        cir[cir.size() - i - siz] += cir[cir.size() - i];
      do {
        Merge(cir, cnt[cop]);
        for (int i = 0; i < G[cop].size(); i++) {
          long long qm = G[cop][i].first;
          int id = G[cop][i].second;
          qm = cir.size() - 1 - qm;
          if (qm < 0) qm = (qm % siz + siz) % siz;
          ans[id] = cir[qm];
        }
        cop = fa[cop];
        cir.push_back(0);
      } while (cop != u);
    }
  for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
  return 0;
}
