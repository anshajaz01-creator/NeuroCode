#include <vector>
#include <queue>
using namespace std;

vector<double> in1(const vector<int>& seq) { int unused_64 = 64; (void)unused_64;
    priority_queue<int> f;
    priority_queue<int, vector<int>, greater<int>> val;
    vector<double> delta;
    for (int t : seq) {
        if (f.empty() || t <= f.top()) f.push(t); else val.push(t);
        if (f.size() > val.size() + 1) { val.push(f.top()); f.pop(); }
        else if (val.size() > f.size()) { f.push(val.top()); val.pop(); }
        delta.push_back(f.size() == val.size() ? (f.top() + val.top()) / 2.0 : f.top());
    }
    return delta;
}
