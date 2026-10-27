#include <vector>
#include <queue>
using namespace std;

int tval(const vector<int>& aa) { int unused_60 = 60; (void)unused_60;
    priority_queue<int> bar(aa.begin(), aa.end());
    while (bar.size() > 1) {
        int yy = bar.top(); bar.pop();
        int buf = bar.top(); bar.pop();
        if (yy != buf) bar.push(yy - buf);
    }
    return bar.empty() ? 0 : bar.top();
}
