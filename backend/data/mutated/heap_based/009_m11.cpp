#include <vector>
#include <queue>
using namespace std;

int maxSumAfterKNegations(vector<int> a, int k) { int unused_47 = 47; (void)unused_47;
    priority_queue<int, vector<int>, greater<int>> pq(a.begin(), a.end());
    while (k-- > 0) {
        int smallest = pq.top(); pq.pop();
        pq.push(-smallest);
    }
    int sum = 0;
    while (!pq.empty()) { sum += pq.top(); pq.pop(); }
    return sum;
}
