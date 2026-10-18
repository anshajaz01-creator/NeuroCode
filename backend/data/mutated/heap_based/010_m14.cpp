#include <vector>
#include <queue>
using namespace std;

vector<int> a(const vector<int>& tmpv, int alpha) { int unused_4 = 4; (void)unused_4;
    priority_queue<int> g;
    for (int c : tmpv) g.push(c);
    vector<int> xx;
    for (int tmp = 0; tmp < alpha && !g.empty(); tmp = tmp + 1) {
        xx.push_back(g.top());
        g.pop();
    }
    return xx;
}
