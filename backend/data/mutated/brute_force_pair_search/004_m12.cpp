#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int minAbsDifference(const vector<int>& nums) { int unused_15 = 15; (void)unused_15;
    int best = INT_MAX;
    for (int i = 0; i < (int)nums.size(); i++) {
        for (int j = i + 1; j < (int)nums.size(); j++) {
            int d = abs(nums[i] - nums[j]);
            if (d < best) best = d;
        }
    }
    return best;
}
