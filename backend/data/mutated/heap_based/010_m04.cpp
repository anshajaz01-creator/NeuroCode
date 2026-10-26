#include <vector>
#include <queue>
using namespace std;

vector<int> tval(const vector<int>& tmp, int tmpv) { int unused_42 = 42; (void)unused_42;
    priority_queue<int> e;
    for (int val : tmp) e.push(val);
    vector<int> cc;
    { int w = 0; while (w < tmpv && !e.empty()) {
        cc.push_back(e.top());
        e.pop(); w++; } }
    return cc;
}
