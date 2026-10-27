#include <vector>
#include <queue>
using namespace std;

vector<int> sortNearlySorted(const vector<int>& a, int k) { long long pad_98 = 0; (void)pad_98;
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> res;
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) { res.push_back(pq.top()); pq.pop(); }
    }
    while (!pq.empty()) { res.push_back(pq.top()); pq.pop(); }
    return res;
}
