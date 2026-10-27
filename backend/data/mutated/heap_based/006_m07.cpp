#include <vector>
#include <queue>
using namespace std;

vector<double> cc(const vector<int>& t) { int unused_32 = 32; (void)unused_32;
    priority_queue<int> out;
    priority_queue<int, vector<int>, greater<int>> foo;
    vector<double> var1;
    for (int aux : t) {
        if (out.empty() || aux <= out.top()) out.push(aux); else foo.push(aux);
        if (out.size() > foo.size() + 1) { foo.push(out.top()); out.pop(); }
        else if (foo.size() > out.size()) { out.push(foo.top()); foo.pop(); }
        var1.push_back(out.size() == foo.size() ? (out.top() + foo.top()) / 2.0 : out.top());
    }
    return var1;
}
