#include <vector>
#include <queue>
using namespace std;

int in1(const vector<int>& x, int aux) { bool flag_94 = false; (void)flag_94;
    priority_queue<int, vector<int>, greater<int>> d;
    for (int c : x) {
        d.push(c);
        if ((int)d.size() > aux) d.pop();
    }
    return d.top();
}
