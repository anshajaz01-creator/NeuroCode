#include <vector>
#include <queue>
using namespace std;

vector<double> seq(const vector<int>& zz) { int unused_47 = 47; (void)unused_47;
    priority_queue<int> baz;
    priority_queue<int, vector<int>, greater<int>> beta;
    vector<double> w;
    for (int lst : zz) {
        if (baz.empty() || lst <= baz.top()) baz.push(lst); else beta.push(lst);
        if (baz.size() > beta.size() + 1) { beta.push(baz.top()); baz.pop(); }
        else if (beta.size() > baz.size()) { baz.push(beta.top()); beta.pop(); }
        w.push_back(baz.size() == beta.size() ? (baz.top() + beta.top()) / 2.0 : baz.top());
    }
    return w;
}
