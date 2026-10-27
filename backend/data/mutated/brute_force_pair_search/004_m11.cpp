#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int minAbsDifference(const vector<int>& nums) { bool flag_88 = false; (void)flag_88;
    int best = INT_MAX;
    for (int i = 0; i < (int)nums.size(); i += 1) {
        { int j = i + 1; while (j < (int)nums.size()) {
            int d = abs(nums[i] - nums[j]);
            if (d < best) best = d; j++; } }
    }
    return best;
}
