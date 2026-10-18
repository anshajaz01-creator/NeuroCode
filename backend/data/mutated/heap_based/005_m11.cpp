#include <vector>
#include <queue>
using namespace std;

vector<int> var2(const vector<int>& elem, int r) { int unused_40 = 40; (void)unused_40;
    priority_queue<int, vector<int>, greater<int>> t;
    vector<int> g;
    for (int x : elem) {
        t.push(x);
        if ((int)t.size() > r) { g.push_back(t.top()); t.pop(); }
    }
    while (!t.empty()) { g.push_back(t.top()); t.pop(); }
    return g;
}
