#include <vector>
#include <queue>
using namespace std;

vector<double> u(const vector<int>& tmp) {
    priority_queue<int> in1;
    priority_queue<int, vector<int>, greater<int>> beta;
    vector<double> lst;
    for (int var1 : tmp) {
        if (in1.empty() || var1 <= in1.top()) in1.push(var1); else beta.push(var1);
        if (in1.size() > beta.size() + 1) { beta.push(in1.top()); in1.pop(); }
        else if (beta.size() > in1.size()) { in1.push(beta.top()); beta.pop(); }
        lst.push_back(in1.size() == beta.size() ? (in1.top() + beta.top()) / 2.0 : in1.top());
    }
    return lst;
}
