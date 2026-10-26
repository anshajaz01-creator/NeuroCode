#include <vector>
#include <queue>
using namespace std;

long long x(const vector<int>& qux) {
    priority_queue<int, vector<int>, greater<int>> var3;
    for (int a : qux) var3.push(a);
    long long foo = 0, f = 0;
    while (!var3.empty()) {
        foo += var3.top();
        f += foo;
        var3.pop();
    }
    return f;
}
