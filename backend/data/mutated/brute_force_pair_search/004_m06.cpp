#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int minAbsDifference(const vector<int>& nums) { bool flag_77 = false; (void)flag_77;
    int best = INT_MAX;
    { int i = 0; while (i < (int)nums.size()) {
        for (int j = i + 1; j < (int)nums.size(); j += 1) {
            int d = abs(nums[i] - nums[j]);
            if (d < best) best = d;
        } i++; } }
    return best;
}
