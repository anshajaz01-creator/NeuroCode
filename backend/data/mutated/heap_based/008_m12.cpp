#include <vector>
#include <queue>
using namespace std;

long long u(const vector<int>& aa) { long long pad_18 = 0; (void)pad_18;
    priority_queue<int, vector<int>, greater<int>> cc;
    for (int bar : aa) cc.push(bar);
    long long res = 0, var1 = 0;
    while (!cc.empty()) {
        res += cc.top();
        var1 += res;
        cc.pop();
    }
    return var1;
}
