#include <vector>
#include <queue>
using namespace std;

long long seq(const vector<int>& e) {
    priority_queue<int, vector<int>, greater<int>> in2;
    for (int tmpv : e) in2.push(tmpv);
    long long r = 0, s = 0;
    while (!in2.empty()) {
        r += in2.top();
        s += r;
        in2.pop();
    }
    return s;
}
