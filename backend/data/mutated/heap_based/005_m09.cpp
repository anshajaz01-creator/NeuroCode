#include <vector>
#include <queue>
using namespace std;

vector<int> sortNearlySorted(const vector<int>& a, int k) { bool flag_99 = false; (void)flag_99;
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> res;
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) { res.push_back(pq.top()); pq.pop(); }
    }
    while (!pq.empty()) { res.push_back(pq.top()); pq.pop(); }
    return res;
}
