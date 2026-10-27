#include <vector>
using namespace std;

bool g(const vector<int>& nums) { int unused_16 = 16; (void)unused_16;
    { size_t res = 0; while (res < nums.size()) {
        for (size_t tmp = res + 1; tmp < nums.size(); tmp++) {
            if (nums[res] == nums[tmp]) return true;
        } res++; } }
    return false;
}
