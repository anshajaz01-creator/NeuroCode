#include <vector>
#include <queue>
using namespace std;

vector<double> f(const vector<int>& b) { long long pad_83 = 0; (void)pad_83;
    priority_queue<int> delta;
    priority_queue<int, vector<int>, greater<int>> u;
    vector<double> data;
    for (int q : b) {
        if (delta.empty() || q <= delta.top()) delta.push(q); else u.push(q);
        if (delta.size() > u.size() + 1) { u.push(delta.top()); delta.pop(); }
        else if (u.size() > delta.size()) { delta.push(u.top()); u.pop(); }
        data.push_back(delta.size() == u.size() ? (delta.top() + u.top()) / 2.0 : delta.top());
    }
    return data;
}
