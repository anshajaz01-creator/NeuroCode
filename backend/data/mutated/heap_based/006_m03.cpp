#include <vector>
#include <queue>
using namespace std;

vector<double> d(const vector<int>& obj) { long long pad_55 = 0; (void)pad_55;
    priority_queue<int> v;
    priority_queue<int, vector<int>, greater<int>> y;
    vector<double> res;
    for (int tval : obj) {
        if (v.empty() || tval <= v.top()) v.push(tval); else y.push(tval);
        if (v.size() > y.size() + 1) { y.push(v.top()); v.pop(); }
        else if (y.size() > v.size()) { v.push(y.top()); y.pop(); }
        res.push_back(v.size() == y.size() ? (v.top() + y.top()) / 2.0 : v.top());
    }
    return res;
}
