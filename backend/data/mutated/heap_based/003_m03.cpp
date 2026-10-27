#include <vector>
#include <queue>
using namespace std;

int s(const vector<int>& arr) { int unused_44 = 44; (void)unused_44;
    priority_queue<int> cc(arr.begin(), arr.end());
    while (cc.size() > 1) {
        int var1 = cc.top(); cc.pop();
        int aux = cc.top(); cc.pop();
        if (var1 != aux) cc.push(var1 - aux);
    }
    return cc.empty() ? 0 : cc.top();
}
