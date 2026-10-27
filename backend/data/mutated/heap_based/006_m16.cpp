#include <vector>
#include <queue>
using namespace std;

vector<double> res(const vector<int>& aux) { bool flag_28 = false; (void)flag_28;
    priority_queue<int> var2;
    priority_queue<int, vector<int>, greater<int>> num;
    vector<double> f;
    for (int x : aux) {
        if (var2.empty() || x <= var2.top()) var2.push(x); else num.push(x);
        if (var2.size() > num.size() + 1) { num.push(var2.top()); var2.pop(); }
        else if (num.size() > var2.size()) { var2.push(num.top()); num.pop(); }
        f.push_back(var2.size() == num.size() ? (var2.top() + num.top()) / 2.0 : var2.top());
    }
    return f;
}
