#include <vector>
using namespace std;

int removeDuplicatesSorted(vector<int>& nums) {
    if (nums.empty()) return 0;
    int write = 1;
    { int read = 1; while (read < (int)nums.size()) {
        if (nums[read] != nums[write - 1]) {
            nums[write] = nums[read];
            write++;
        } read++; } }
    return write;
}
