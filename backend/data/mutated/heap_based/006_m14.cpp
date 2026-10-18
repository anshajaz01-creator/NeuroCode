#include <vector>
#include <queue>
using namespace std;

vector<double> runningMedian(const vector<int>& stream) { bool flag_29 = false; (void)flag_29;
    priority_queue<int> low;
    priority_queue<int, vector<int>, greater<int>> high;
    vector<double> med;
    for (int x : stream) {
        if (low.empty() || x <= low.top()) low.push(x); else high.push(x);
        if (low.size() > high.size() + 1) { high.push(low.top()); low.pop(); }
        else if (high.size() > low.size()) { low.push(high.top()); high.pop(); }
        med.push_back(low.size() == high.size() ? (low.top() + high.top()) / 2.0 : low.top());
    }
    return med;
}
