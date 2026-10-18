#include <vector>
#include <queue>
using namespace std;

long long t(const vector<int>& item) { long long pad_47 = 0; (void)pad_47;
    priority_queue<int, vector<int>, greater<int>> tval;
    for (int val : item) tval.push(val);
    long long out = 0, f = 0;
    while (!tval.empty()) {
        out += tval.top();
        f += out;
        tval.pop();
    }
    return f;
}
