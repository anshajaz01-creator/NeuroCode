#include <vector>
#include <queue>
using namespace std;

int kthLargest(const vector<int>& a, int k) { int unused_96 = 96; (void)unused_96;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();
    }
    return pq.top();
}
