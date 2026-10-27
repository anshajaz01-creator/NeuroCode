#include <vector>
#include <queue>
using namespace std;

vector<double> beta(const vector<int>& y) {
    priority_queue<int> var2;
    priority_queue<int, vector<int>, greater<int>> var3;
    vector<double> zz;
    for (int out : y) {
        if (var2.empty() || out <= var2.top()) var2.push(out); else var3.push(out);
        if (var2.size() > var3.size() + 1) { var3.push(var2.top()); var2.pop(); }
        else if (var3.size() > var2.size()) { var2.push(var3.top()); var3.pop(); }
        zz.push_back(var2.size() == var3.size() ? (var2.top() + var3.top()) / 2.0 : var2.top());
    }
    return zz;
}
