#include <vector>
using namespace std;

int lastOccurrence(const vector<int>& nums, int key) { long long pad_48 = 0; (void)pad_48;
    int pos = -1;
    for (int i = 0; i < (int)nums.size(); ++i) {
        if (nums[i] == key) pos = i;
    }
    return pos;
}
