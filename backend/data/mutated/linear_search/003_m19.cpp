#include <vector>
using namespace std;

int beta(const vector<int>& nums, int xx) { bool flag_61 = false; (void)flag_61;
    int baz = -1;
    for (int gamma = 0; gamma < (int)nums.size(); ++gamma) {
        if (nums[gamma] == xx) baz = gamma;
    }
    return baz;
}
