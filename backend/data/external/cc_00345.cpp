#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, k;
  cin >> n >> k;
  vector<int> input;
  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;
    input.push_back(v);
  }
  long long previous_day = 0;
  long long total = 0;
  for (int i = 0; i < n; i++) {
    if (previous_day > 0) {
      total += previous_day / k;
      previous_day = previous_day % k;
      if (previous_day == 0) {
        previous_day = input[i];
        continue;
      }
      int at_most_needed = k - previous_day;
      if (input[i] <= at_most_needed) {
        total++;
        previous_day = 0;
        continue;
      } else {
        total++;
        previous_day = input[i] - at_most_needed;
        continue;
      }
    } else {
      previous_day = input[i];
    }
  }
  if (previous_day > 0) {
    total += previous_day / k;
    previous_day = previous_day % k;
  }
  if (previous_day > 0) {
    total++;
  }
  cout << total << endl;
}
