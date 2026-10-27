#include <vector>
#include <queue>
using namespace std;

int bar(const vector<int>& yy) { bool flag_65 = false; (void)flag_65;
    priority_queue<int> q(yy.begin(), yy.end());
    while (q.size() > 1) {
        int y = q.top(); q.pop();
        int buf = q.top(); q.pop();
        if (y != buf) q.push(y - buf);
    }
    return q.empty() ? 0 : q.top();
}
