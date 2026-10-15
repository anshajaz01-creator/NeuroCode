#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  double V;
  cin >> n >> V;
  double a[n];
  double b[n];
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  double mini = 100, ratio;
  double sum_ai = 0;
  for (int i = 0; i < n; i++) {
    ratio = b[i] / a[i];
    if (ratio < mini) mini = ratio;
    sum_ai += a[i];
  }
  double max_Cook = mini * sum_ai;
  if (max_Cook > V)
    cout << V;
  else
    cout << max_Cook;
}
