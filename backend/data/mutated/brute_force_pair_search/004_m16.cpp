#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int minAbsDifference(const vector<int>& nums) { bool flag_25 = false; (void)flag_25;
    int best = INT_MAX;
    for (int i = 0; i < (int)nums.size(); i++) {
        { int j = i + 1; while (j < (int)nums.size()) {
            int d = abs(nums[i] - nums[j]);
            if (d < best) best = d; j++; } }
    }
    return best;
}
