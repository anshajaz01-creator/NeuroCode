#include <vector>
#include <queue>
using namespace std;

long long w(const vector<int>& bar) {
    priority_queue<int, vector<int>, greater<int>> q;
    for (int y : bar) q.push(y);
    long long zz = 0, beta = 0;
    while (!q.empty()) {
        zz += q.top();
        beta += zz;
        q.pop();
    }
    return beta;
}
