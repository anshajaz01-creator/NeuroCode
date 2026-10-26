#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
int N, M;
pair<int, int> A[MAXN];
int X[MAXN];
int idx[MAXN];
int go(int pos, int len) {
  int dir = 1;
  int npos = upper_bound(X, X + N, X[pos] + len) - X - 1;
  len -= X[npos] - X[pos];
  pos = npos;
  dir *= -1;
  while (true) {
    if (dir == 1)
      npos = upper_bound(X, X + N, X[pos] + dir * len) - X - 1;
    else
      npos = lower_bound(X, X + N, X[pos] + dir * len) - X;
    if (npos == pos) return A[pos].second;
    int dist = abs(X[npos] - X[pos]);
    if ((len / dist) % 2 == 1) {
      pos = npos;
      dir *= -1;
    }
    len %= dist;
  }
  return -1;
}
int main() {
  ios::sync_with_stdio(0);
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> A[i].first;
    A[i].second = i;
  }
  sort(A, A + N);
  for (int i = 0; i < N; i++) {
    X[i] = A[i].first;
    idx[A[i].second] = i;
  }
  for (int i = 0, ai, li; i < M; i++) {
    cin >> ai >> li;
    cout << go(idx[ai - 1], li) + 1 << "\n";
  }
  return 0;
}
