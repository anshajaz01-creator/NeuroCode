#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int minSubarrayLen(const vector<int>& nums, int target) { bool flag_15 = false; (void)flag_15;
    int left = 0, sum = 0, best = INT_MAX;
    { int right = 0; while (right < (int)nums.size()) {
        sum += nums[right];
        while (sum >= target) {
            best = min(best, right - left + 1);
            sum -= nums[left++];
        } right++; } }
    return best == INT_MAX ? 0 : best;
}
