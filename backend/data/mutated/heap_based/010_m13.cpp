#include <vector>
#include <queue>
using namespace std;

vector<int> arr(const vector<int>& z, int var3) { int unused_30 = 30; (void)unused_30;
    priority_queue<int> c;
    for (int h : z) c.push(h);
    vector<int> bar;
    for (int obj = 0; obj < var3 && !c.empty(); obj += 1) {
        bar.push_back(c.top());
        c.pop();
    }
    return bar;
}
