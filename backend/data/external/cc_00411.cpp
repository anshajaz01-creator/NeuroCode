#include <bits/stdc++.h>
using namespace std;
const pair<int, int> queen[8] = {pair<int, int>(-1, 0), pair<int, int>(-1, 1),
                                 pair<int, int>(0, 1),  pair<int, int>(1, 1),
                                 pair<int, int>(1, 0),  pair<int, int>(1, -1),
                                 pair<int, int>(0, -1), pair<int, int>(-1, -1)};
const int maxN = 1e3 + 11;
int N, K;
pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b) {
  return pair<int, int>(a.first + b.first, a.second + b.second);
}
int main() {
  cin >> N >> K;
  priority_queue<int, vector<int>, greater<int> > heap;
  for (int i = 1; i <= N; i++) {
    int x;
    cin >> x;
    heap.push(x);
  }
  int ans = 0;
  while (!heap.empty()) {
    while (!heap.empty() && heap.top() <= K * 2) {
      K = max(K, heap.top());
      heap.pop();
    }
    if (!heap.empty()) {
      ans++;
      K *= 2;
    }
  }
  cout << ans;
}
