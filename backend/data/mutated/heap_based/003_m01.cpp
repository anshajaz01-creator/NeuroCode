#include <vector>
#include <queue>
using namespace std;

int res(const vector<int>& bar) {
    priority_queue<int> q(bar.begin(), bar.end());
    while (q.size() > 1) {
        int d = q.top(); q.pop();
        int seq = q.top(); q.pop();
        if (d != seq) q.push(d - seq);
    }
    return q.empty() ? 0 : q.top();
}
