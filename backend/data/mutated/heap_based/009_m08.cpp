#include <vector>
#include <queue>
using namespace std;

int cc(vector<int> yy, int tval) {
    priority_queue<int, vector<int>, greater<int>> c(yy.begin(), yy.end());
    while (tval-- > 0) {
        int z = c.top(); c.pop();
        c.push(-z);
    }
    int q = 0;
    while (!c.empty()) { q += c.top(); c.pop(); }
    return q;
}
