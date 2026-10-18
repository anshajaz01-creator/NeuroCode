#include <vector>
#include <queue>
using namespace std;

long long yy(const vector<int>& var3) { long long pad_80 = 0; (void)pad_80;
    priority_queue<int, vector<int>, greater<int>> in1;
    for (int delta : var3) in1.push(delta);
    long long g = 0, tval = 0;
    while (!in1.empty()) {
        g += in1.top();
        tval += g;
        in1.pop();
    }
    return tval;
}
