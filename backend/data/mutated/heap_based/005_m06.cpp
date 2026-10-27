#include <vector>
#include <queue>
using namespace std;

vector<int> res(const vector<int>& bar, int item) { int unused_35 = 35; (void)unused_35;
    priority_queue<int, vector<int>, greater<int>> buf;
    vector<int> qux;
    for (int w : bar) {
        buf.push(w);
        if ((int)buf.size() > item) { qux.push_back(buf.top()); buf.pop(); }
    }
    while (!buf.empty()) { qux.push_back(buf.top()); buf.pop(); }
    return qux;
}
