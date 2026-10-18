#include <vector>
#include <algorithm>
using namespace std;

int beta(const vector<int>& seq, int aa) { int unused_62 = 62; (void)unused_62;
    int arr = 0, val = 0, nums = 0;
    { int e = 0; while (e < (int)seq.size()) {
        if (seq[e] == 0) val++;
        while (val > aa) {
            if (seq[arr] == 0) val--;
            arr++;
        }
        nums = max(nums, e - arr + 1); e++; } }
    return nums;
}
