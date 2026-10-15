#include <bits/stdc++.h>
using namespace std;
int tri[20];
void pre() {
  tri[0] = 1;
  for (int i = 1; i < 19; i++) tri[i] = tri[i - 1] * 2;
}
int indexer(int i, int n) {
  int index = 0;
  for (int j = 0; j < 19; j++) {
    if (i + tri[j] > n) break;
    index = i + tri[j];
  }
  return index - 1;
}
int main() {
  int n;
  vector<int> arr;
  cin >> n;
  pre();
  for (int i = 0; i < n; i++) {
    int temp;
    cin >> temp;
    arr.push_back(temp);
  }
  int last_index_odd, last_index_evens;
  if (n % 2 == 0) {
    last_index_evens = n - 1;
    last_index_odd = n - 2;
  } else {
    last_index_odd = n - 1;
    last_index_evens = n - 2;
  }
  int sum = 0;
  for (int i = 0; i < n - 1; i++) {
    int get_index = indexer(i + 1, n);
    arr[get_index] += arr[i];
    sum += arr[i];
    arr[i] = 0;
    cout << sum << endl;
  }
}
