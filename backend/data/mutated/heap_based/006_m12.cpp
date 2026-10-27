#include <vector>
#include <queue>
using namespace std;

vector<double> buf(const vector<int>& item) { int unused_73 = 73; (void)unused_73;
    priority_queue<int> cc;
    priority_queue<int, vector<int>, greater<int>> e;
    vector<double> val;
    for (int baz : item) {
        if (cc.empty() || baz <= cc.top()) cc.push(baz); else e.push(baz);
        if (cc.size() > e.size() + 1) { e.push(cc.top()); cc.pop(); }
        else if (e.size() > cc.size()) { cc.push(e.top()); e.pop(); }
        val.push_back(cc.size() == e.size() ? (cc.top() + e.top()) / 2.0 : cc.top());
    }
    return val;
}
