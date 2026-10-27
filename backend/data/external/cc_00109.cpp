#include <bits/stdc++.h>
using namespace std;
const int MAXSUM = 50000 * 24 + 10;
void my_sort(vector<pair<int, int>>& V) {
  vector<int> x(MAXSUM, -1);
  for (int i = 0; i < (int)V.size(); i++) x[V[i].first] = V[i].second;
  V.clear();
  for (int i = 0; i < MAXSUM; i++)
    if (x[i] != -1) V.push_back({i, x[i]});
}
vector<vector<pair<int, int>>> calc(vector<int>& x) {
  int n = x.size();
  vector<vector<pair<int, int>>> V(n + 1);
  for (int mask = 0; mask < (1 << n); mask++) {
    int sum = 0;
    for (int i = 0; i < n; i++)
      if ((1 << i) & mask) sum += x[i];
    V[__builtin_popcount(mask)].push_back({sum, mask});
  }
  for (int i = 0; i <= n; i++) my_sort(V[i]);
  return V;
}
void print(vector<int>& x, int mask, bool reversed) {
  int n = x.size();
  vector<int> y;
  for (int i = 0; i < n; i++)
    if ((1 << i) & mask) y.push_back(x[i]);
  if (reversed) reverse(y.begin(), y.end());
  for (int i = 0; i < (int)y.size(); i++) cout << y[i] << " ";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector<int> x(2 * n);
  for (int i = 0; i < 2 * n; i++) cin >> x[i];
  sort(x.begin(), x.end());
  vector<int> a(n - 1), b(n - 1);
  for (int i = 0; i < n - 1; i++) {
    a[i] = x[2 + i];
    b[i] = x[n + 1 + i];
  }
  auto A = calc(a);
  auto B = calc(b);
  int goal = (A[n - 1][0].first + B[n - 1][0].first) / 2;
  int best = -1, mask_a, mask_b;
  for (int k = 0; k < n; k++) {
    int j = (int)B[n - 1 - k].size() - 1;
    for (int i = 0; i < (int)A[k].size(); i++) {
      while (j >= 0 && A[k][i].first + B[n - 1 - k][j].first > goal) j--;
      if (j == -1) break;
      int tmp = A[k][i].first + B[n - 1 - k][j].first;
      if (tmp > best) {
        best = tmp;
        mask_a = A[k][i].second;
        mask_b = B[n - 1 - k][j].second;
      }
    }
  }
  cout << x[0] << " ";
  print(a, mask_a, false);
  print(b, mask_b, false);
  cout << "\n";
  print(b, ~mask_b, true);
  print(a, ~mask_a, true);
  cout << x[1] << "\n";
  return 0;
}
