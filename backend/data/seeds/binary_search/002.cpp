#include <vector>
using namespace std;

int firstOccurrence(const vector<int>& nums, int x) {
    int left = 0, right = nums.size() - 1, ans = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] >= x) {
            if (nums[mid] == x) ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}
