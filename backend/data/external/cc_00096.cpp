#include <bits/stdc++.h>
using namespace std;
const int INF = 57 * 1e8;
void find_available_x(vector<vector<int>>& v, int x) {
  int count_operations = 0;
  while (x > 0) {
    v[x].push_back(count_operations);
    x /= 2;
    ++count_operations;
  }
}
int sum_count_operation_for_each_elem(vector<int> v, int k) {
  int sum = 0;
  for (int i = 0; i < k; ++i) {
    sum += v[i];
  }
  return sum;
}
int main() {
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  vector<vector<int>> available_x(2 * 1e5 + 57, vector<int>());
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
    find_available_x(available_x, v[i]);
  }
  int min_count_operation = INF;
  for (int i = 0; i < available_x.size(); ++i) {
    if (available_x[i].size() >= k) {
      sort(available_x[i].begin(), available_x[i].end());
      min_count_operation =
          min(min_count_operation,
              sum_count_operation_for_each_elem(available_x[i], k));
    }
  }
  cout << min_count_operation;
  return 0;
}
