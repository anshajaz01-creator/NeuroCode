#include <bits/stdc++.h>
using namespace std;
int n, k, v, cnt, mx;
unordered_map<int, int> frq, play, cost;
int mem[600][6000];
int dp(int i, int sum) {
  if (i == cnt) {
    return 0;
  }
  int& ret = mem[i][sum];
  if (~ret) return ret;
  ret = 0;
  for (int j = 1; j <= k; j++) {
    if (sum - j >= 0) {
      ret = max(ret, cost[j] + dp(i + 1, sum - j));
    }
  }
  return ret;
}
int main() {
  cin >> n >> k;
  for (int i = 0; i < n * k; i++) {
    cin >> v;
    frq[v]++;
  }
  for (int i = 0; i < n; i++) {
    cin >> v;
    play[v]++;
  }
  for (int i = 1; i <= k; i++) {
    cin >> cost[i];
  }
  int sum = 0;
  for (auto i : play) {
    memset(mem, -1, sizeof mem);
    cnt = i.second, mx = frq[i.first];
    sum += dp(0, mx);
  }
  cout << sum;
}
