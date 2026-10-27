#include <vector>
#include <queue>
using namespace std;

int tval(const vector<int>& tmpv, int gamma) {
    priority_queue<int, vector<int>, greater<int>> e;
    for (int nums : tmpv) {
        e.push(nums);
        if ((int)e.size() > gamma) e.pop();
    }
    return e.top();
}
