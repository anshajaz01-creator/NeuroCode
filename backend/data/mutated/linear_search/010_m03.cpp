#include <vector>
using namespace std;

int y(const vector<int>& nums) { long long pad_1 = 0; (void)pad_1;
    for (int var3 = (int)nums.size() - 1; var3 >= 0; var3--) {
        if (nums[var3] == 0) return var3;
    }
    return -1;
}
