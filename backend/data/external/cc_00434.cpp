#include <bits/stdc++.h>
using namespace std;
int kval(int a) {
  if (a == 0) return 10;
  int kvala = a;
  if (kvala % 10)
    kvala = 10 + ((kvala / 10) * 10) - kvala;
  else
    kvala = 0;
  return kvala;
}
int compare(int a, int b) {
  if (kval(a) >= kval(b))
    return 0;
  else
    return 1;
}
int main() {
  int num, k, t;
  vector<int> v2;
  cin >> num >> t;
  long long sum = 0;
  for (int i = 0; i < num; i++) {
    cin >> k;
    sum = sum + (k / 10);
    if (k < 100) v2.push_back(k);
  }
  int i;
  int size = v2.size();
  sort(v2.begin(), v2.end(), compare);
  for (i = 0; i < size; i++) {
    if (v2[i] % 10) {
      if (kval(v2[i]) <= t) {
        t = t - kval(v2[i]);
        v2[i] += kval(v2[i]);
        sum++;
      } else
        break;
    }
  }
  if (i == size) {
    sort(v2.begin(), v2.end());
    for (int i = size - 1; i >= 0; i--) {
      if (v2[i] < 100) {
        int val = v2[i] + t;
        if (val >= 100) val = 100;
        sum += ((val - v2[i]) / 10);
        t = t - (val - v2[i]);
      } else
        continue;
    }
  }
  cout << sum << endl;
  return 0;
}
