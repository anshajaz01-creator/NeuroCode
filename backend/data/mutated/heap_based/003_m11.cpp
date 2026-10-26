#include <vector>
#include <queue>
using namespace std;

int s(const vector<int>& x) {
    priority_queue<int> nums(x.begin(), x.end());
    while (nums.size() > 1) {
        int in1 = nums.top(); nums.pop();
        int num = nums.top(); nums.pop();
        if (in1 != num) nums.push(in1 - num);
    }
    return nums.empty() ? 0 : nums.top();
}
