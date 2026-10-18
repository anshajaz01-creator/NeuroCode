#include <vector>
#include <queue>
using namespace std;

int f(vector<int> y, int foo) { bool flag_7 = false; (void)flag_7;
    priority_queue<int, vector<int>, greater<int>> in1(y.begin(), y.end());
    while (foo-- > 0) {
        int res = in1.top(); in1.pop();
        in1.push(-res);
    }
    int in2 = 0;
    while (!in1.empty()) { in2 += in1.top(); in1.pop(); }
    return in2;
}
