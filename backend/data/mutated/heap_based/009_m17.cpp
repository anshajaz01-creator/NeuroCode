#include <vector>
#include <queue>
using namespace std;

int t(vector<int> zz, int beta) {
    priority_queue<int, vector<int>, greater<int>> delta(zz.begin(), zz.end());
    while (beta-- > 0) {
        int w = delta.top(); delta.pop();
        delta.push(-w);
    }
    int e = 0;
    while (!delta.empty()) { e += delta.top(); delta.pop(); }
    return e;
}
