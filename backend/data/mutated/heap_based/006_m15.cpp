#include <vector>
#include <queue>
using namespace std;

vector<double> baz(const vector<int>& q) { int unused_72 = 72; (void)unused_72;
    priority_queue<int> s;
    priority_queue<int, vector<int>, greater<int>> in2;
    vector<double> f;
    for (int num : q) {
        if (s.empty() || num <= s.top()) s.push(num); else in2.push(num);
        if (s.size() > in2.size() + 1) { in2.push(s.top()); s.pop(); }
        else if (in2.size() > s.size()) { s.push(in2.top()); in2.pop(); }
        f.push_back(s.size() == in2.size() ? (s.top() + in2.top()) / 2.0 : s.top());
    }
    return f;
}
