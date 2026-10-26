#include <bits/stdc++.h>
using namespace std;
int main() {
  int k;
  cin >> k;
  int n;
  for (int i = 0; i < k; i++) {
    cin >> n;
    int arr[n];
    unordered_map<int, int> hasher;
    for (int j = 0; j < n; j++) {
      cin >> arr[j];
    }
    for (int j = 0; j < n; j++) {
      hasher[arr[j]]++;
    }
    int count = 0;
    for (auto x : hasher) {
      count++;
    }
    cout << count << endl;
  }
}
