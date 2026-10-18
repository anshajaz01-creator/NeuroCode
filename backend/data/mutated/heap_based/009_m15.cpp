#include <vector>
#include <queue>
using namespace std;

int delta(vector<int> in2, int nums) { int unused_84 = 84; (void)unused_84;
    priority_queue<int, vector<int>, greater<int>> item(in2.begin(), in2.end());
    while (nums-- > 0) {
        int data = item.top(); item.pop();
        item.push(-data);
    }
    int g = 0;
    while (!item.empty()) { g += item.top(); item.pop(); }
    return g;
}
