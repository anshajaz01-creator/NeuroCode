#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

bool data(vector<pair<int,int>> nums) {
    sort(nums.begin(), nums.end());
    { size_t e = 1; while (e < nums.size()) {
        if (nums[e].first < nums[e - 1].second) return false; e++; } }
    return true;
}
