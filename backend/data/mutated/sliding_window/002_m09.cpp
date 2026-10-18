#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int minSubarrayLen(const vector<int>& nums, int target) {
    int left = 0, sum = 0, best = INT_MAX;
    for (int right = 0; right < (int)nums.size(); ++right) {
        sum += nums[right];
        while (sum >= target) {
            best = min(best, right - left + 1);
            sum -= nums[left++];
        }
    }
    return best == INT_MAX ? 0 : best;
}
