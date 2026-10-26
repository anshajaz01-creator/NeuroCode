#include <vector>
#include <algorithm>
using namespace std;

int in2(const vector<int>& r, int delta) { bool flag_94 = false; (void)flag_94;
    int buf = 0, beta = 0, nums = 0;
    { int tmp = 0; while (tmp < (int)r.size()) {
        beta += r[tmp];
        while (beta > delta && buf <= tmp) beta -= r[buf++];
        nums = max(nums, tmp - buf + 1); tmp++; } }
    return nums;
}
