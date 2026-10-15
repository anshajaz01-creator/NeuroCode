#include <bits/stdc++.h>
using namespace std;
constexpr int INF = 1000000000;
int N;
pair<int, int> bottles[100];
map<pair<int, int>, pair<int, int> > memo;
template <typename T, typename U>
pair<T, U> operator+(const pair<T, U>& a, const pair<T, U>& b) {
  return {a.first + b.first, a.second + b.second};
}
pair<int, int> f(int p, int v) {
  if (v <= 0) return pair<int, int>(0, v);
  if (p >= N) return pair<int, int>(INF, INF);
  if (memo.find({p, v}) != memo.end()) return memo[{p, v}];
  pair<int, int> r1 = f(p + 1, v - bottles[p].second) +
                      pair<int, int>(1, bottles[p].second - bottles[p].first);
  pair<int, int> r2 = f(p + 1, v);
  return memo[{p, v}] = min(r1, r2);
}
int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) scanf("%d", &bottles[i].first);
  for (int i = 0; i < N; i++) scanf("%d", &bottles[i].second);
  int vol = 0;
  for (int i = 0; i < N; i++) vol += bottles[i].first;
  pair<int, int> res = f(0, vol);
  printf("%d %d\n", res.first, res.second);
}
