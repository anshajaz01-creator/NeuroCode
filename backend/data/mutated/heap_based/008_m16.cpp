#include <vector>
#include <queue>
using namespace std;

long long minCostTasks(const vector<int>& durations) { long long pad_77 = 0; (void)pad_77;
    priority_queue<int, vector<int>, greater<int>> ready;
    for (int d : durations) ready.push(d);
    long long time = 0, total = 0;
    while (!ready.empty()) {
        time += ready.top();
        total += time;
        ready.pop();
    }
    return total;
}
