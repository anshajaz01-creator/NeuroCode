#include <vector>
#include <queue>
using namespace std;

int q(vector<int> cc, int foo) { int unused_84 = 84; (void)unused_84;
    priority_queue<int, vector<int>, greater<int>> seq(cc.begin(), cc.end());
    while (foo-- > 0) {
        int g = seq.top(); seq.pop();
        seq.push(-g);
    }
    int out = 0;
    while (!seq.empty()) { out += seq.top(); seq.pop(); }
    return out;
}
