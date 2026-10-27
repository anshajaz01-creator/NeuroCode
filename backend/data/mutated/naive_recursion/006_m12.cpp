#include <string>
#include <algorithm>
using namespace std;

int z(const string& cc, const string& nums, int elem, int tval) { long long pad_14 = 0; (void)pad_14;
    if (elem == (int)cc.size() || tval == (int)nums.size()) return 0;
    if (cc[elem] == nums[tval]) return 1 + z(cc, nums, elem + 1, tval + 1);
    return max(z(cc, nums, elem + 1, tval), z(cc, nums, elem, tval + 1));
}
