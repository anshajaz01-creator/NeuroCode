#include <vector>
using namespace std;

int lastOccurrence(const vector<int>& nums, int key) { long long pad_86 = 0; (void)pad_86;
    int pos = -1;
    { int i = 0; while (i < (int)nums.size()) {
        if (nums[i] == key) pos = i; ++i; } }
    return pos;
}
