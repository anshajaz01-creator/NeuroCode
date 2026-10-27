#include <vector>
#include <queue>
using namespace std;

vector<double> s(const vector<int>& val) {
    priority_queue<int> baz;
    priority_queue<int, vector<int>, greater<int>> aa;
    vector<double> tmp;
    for (int seq : val) {
        if (baz.empty() || seq <= baz.top()) baz.push(seq); else aa.push(seq);
        if (baz.size() > aa.size() + 1) { aa.push(baz.top()); baz.pop(); }
        else if (aa.size() > baz.size()) { baz.push(aa.top()); aa.pop(); }
        tmp.push_back(baz.size() == aa.size() ? (baz.top() + aa.top()) / 2.0 : baz.top());
    }
    return tmp;
}
