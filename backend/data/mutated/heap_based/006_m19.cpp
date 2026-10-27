#include <vector>
#include <queue>
using namespace std;

vector<double> baz(const vector<int>& res) { int unused_83 = 83; (void)unused_83;
    priority_queue<int> z;
    priority_queue<int, vector<int>, greater<int>> gamma;
    vector<double> delta;
    for (int w : res) {
        if (z.empty() || w <= z.top()) z.push(w); else gamma.push(w);
        if (z.size() > gamma.size() + 1) { gamma.push(z.top()); z.pop(); }
        else if (gamma.size() > z.size()) { z.push(gamma.top()); gamma.pop(); }
        delta.push_back(z.size() == gamma.size() ? (z.top() + gamma.top()) / 2.0 : z.top());
    }
    return delta;
}
