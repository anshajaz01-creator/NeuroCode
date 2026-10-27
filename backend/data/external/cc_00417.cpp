#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ;
  long long n, a, b;
  cin >> n >> a >> b;
  long long firstHole;
  cin >> firstHole;
  long long totalSize = 0;
  vector<long long> arr(n - 1, 0);
  for (long long i = 0; i < n - 1; i++) {
    cin >> arr[i];
    totalSize += arr[i];
  }
  totalSize += firstHole;
  float possible = (1.00 * firstHole * a) / (1.00 * totalSize);
  long long blocked = 0;
  sort(arr.begin(), arr.end(), greater<long long>());
  for (long long i = 0; i < n - 1; i++) {
    if (possible >= b) {
      break;
    }
    totalSize -= arr[i];
    possible = (1.00 * firstHole * a) / (1.00 * totalSize);
    ++blocked;
  }
  cout << blocked;
  return 0;
}
