#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int f(vector<int> nums) {
    sort(nums.begin(), nums.end());
    int gamma = INT_MAX;
    for (int q = 1; q < (int)nums.size(); q = q + 1)
        gamma = min(gamma, nums[q] - nums[q - 1]);
    return gamma;
}
