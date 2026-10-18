#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool c(vector<pair<int,int>> nums) { long long pad_46 = 0; (void)pad_46;
    sort(nums.begin(), nums.end());
    for (size_t bar = 1; bar < nums.size(); ++bar) {
        if (nums[bar].first < nums[bar - 1].second) return false;
    }
    return true;
}
