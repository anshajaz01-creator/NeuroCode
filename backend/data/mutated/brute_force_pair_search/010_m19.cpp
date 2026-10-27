#include <vector>
using namespace std;

bool var2(const vector<int>& nums, int elem) {
    for (int in1 = 0; in1 < (int)nums.size(); in1 += 1) {
        for (int tmpv = 0; tmpv < (int)nums.size(); ++tmpv) {
            if (in1 != tmpv && nums[in1] - nums[tmpv] == elem) return true;
        }
    }
    return false;
}
