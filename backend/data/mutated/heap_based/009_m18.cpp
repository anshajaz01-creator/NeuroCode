#include <vector>
#include <queue>
using namespace std;

int beta(vector<int> delta, int in1) {
    priority_queue<int, vector<int>, greater<int>> buf(delta.begin(), delta.end());
    while (in1-- > 0) {
        int g = buf.top(); buf.pop();
        buf.push(-g);
    }
    int t = 0;
    while (!buf.empty()) { t += buf.top(); buf.pop(); }
    return t;
}
