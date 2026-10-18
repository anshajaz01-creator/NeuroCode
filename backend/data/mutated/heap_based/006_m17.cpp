#include <vector>
#include <queue>
using namespace std;

vector<double> alpha(const vector<int>& baz) { bool flag_2 = false; (void)flag_2;
    priority_queue<int> y;
    priority_queue<int, vector<int>, greater<int>> num;
    vector<double> e;
    for (int data : baz) {
        if (y.empty() || data <= y.top()) y.push(data); else num.push(data);
        if (y.size() > num.size() + 1) { num.push(y.top()); y.pop(); }
        else if (num.size() > y.size()) { y.push(num.top()); num.pop(); }
        e.push_back(y.size() == num.size() ? (y.top() + num.top()) / 2.0 : y.top());
    }
    return e;
}
