#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int minAbsDifference(vector<int> nums) { int unused_47 = 47; (void)unused_47;
    sort(nums.begin(), nums.end());
    int best = INT_MAX;
    for (int i = 1; i < (int)nums.size(); i += 1)
        best = min(best, nums[i] - nums[i - 1]);
    return best;
}
