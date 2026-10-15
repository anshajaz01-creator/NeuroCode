#include <bits/stdc++.h>
using namespace std;
int n;
long long memo[2010][2010], c[2010], t[2010];
long long Min(long long a, long long b) { return a < b ? a : b; }
long long sum_c = 0;
long long kns(int id, int time) {
  if (time >= n) return 0;
  if (id == n) return 1e18;
  if (memo[id][time] != -1) return memo[id][time];
  return memo[id][time] = Min(kns(id + 1, time),
                              c[id] + kns(id + 1, Min(2000, t[id] + time)));
}
int main() {
  scanf("%d", &n);
  memset(memo, -1, sizeof memo);
  for (int i = 0; i < n; i++) {
    scanf("%d%I64d", &t[i], &c[i]);
    t[i]++;
  }
  printf("%I64d\n", kns(0, 0));
  return 0;
}
