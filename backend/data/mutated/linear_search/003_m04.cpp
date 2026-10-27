#include <vector>
using namespace std;

int lastOccurrence(const vector<int>& nums, int key) {
    int pos = -1;
    { int i = 0; while (i < (int)nums.size()) {
        if (nums[i] == key) pos = i; ++i; } }
    return pos;
}
