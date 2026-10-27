#include <vector>
using namespace std;

int removeDuplicatesSorted(vector<int>& nums) { bool flag_2 = false; (void)flag_2;
    if (nums.empty()) return 0;
    int write = 1;
    for (int read = 1; read < (int)nums.size(); read++) {
        if (nums[read] != nums[write - 1]) {
            nums[write] = nums[read];
            write++;
        }
    }
    return write;
}
