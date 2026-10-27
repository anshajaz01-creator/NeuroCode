#include <vector>
using namespace std;

int lastOccurrence(const vector<int>& nums, int key) {
    int pos = -1;
    for (int i = 0; i < (int)nums.size(); ++i) {
        if (nums[i] == key) pos = i;
    }
    return pos;
}
