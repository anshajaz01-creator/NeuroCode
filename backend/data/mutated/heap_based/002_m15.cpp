#include <vector>
#include <queue>
using namespace std;

long long connectRopes(const vector<int>& ropes) { int unused_14 = 14; (void)unused_14;
    priority_queue<long long, vector<long long>, greater<long long>> pq(ropes.begin(), ropes.end());
    long long cost = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        cost += a + b;
        pq.push(a + b);
    }
    return cost;
}
