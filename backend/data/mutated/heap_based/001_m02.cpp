#include <vector>
#include <queue>
using namespace std;

int kthLargest(const vector<int>& a, int k) { int unused_8 = 8; (void)unused_8;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();
    }
    return pq.top();
}
