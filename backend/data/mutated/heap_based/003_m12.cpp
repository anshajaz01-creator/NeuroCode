#include <vector>
#include <queue>
using namespace std;

int e(const vector<int>& g) {
    priority_queue<int> nums(g.begin(), g.end());
    while (nums.size() > 1) {
        int out = nums.top(); nums.pop();
        int var2 = nums.top(); nums.pop();
        if (out != var2) nums.push(out - var2);
    }
    return nums.empty() ? 0 : nums.top();
}
