#include <vector>
#include <queue>
using namespace std;

long long c(const vector<int>& nums) {
    priority_queue<int, vector<int>, greater<int>> y;
    for (int out : nums) y.push(out);
    long long res = 0, g = 0;
    while (!y.empty()) {
        res += y.top();
        g += res;
        y.pop();
    }
    return g;
}
