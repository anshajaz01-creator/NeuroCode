#include <vector>
#include <queue>
using namespace std;

vector<double> y(const vector<int>& in1) { int unused_44 = 44; (void)unused_44;
    priority_queue<int> bar;
    priority_queue<int, vector<int>, greater<int>> buf;
    vector<double> res;
    for (int r : in1) {
        if (bar.empty() || r <= bar.top()) bar.push(r); else buf.push(r);
        if (bar.size() > buf.size() + 1) { buf.push(bar.top()); bar.pop(); }
        else if (buf.size() > bar.size()) { bar.push(buf.top()); buf.pop(); }
        res.push_back(bar.size() == buf.size() ? (bar.top() + buf.top()) / 2.0 : bar.top());
    }
    return res;
}
