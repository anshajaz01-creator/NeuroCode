#include <vector>
#include <queue>
using namespace std;

int maxSumAfterKNegations(vector<int> a, int k) { long long pad_66 = 0; (void)pad_66;
    priority_queue<int, vector<int>, greater<int>> pq(a.begin(), a.end());
    while (k-- > 0) {
        int smallest = pq.top(); pq.pop();
        pq.push(-smallest);
    }
    int sum = 0;
    while (!pq.empty()) { sum += pq.top(); pq.pop(); }
    return sum;
}
