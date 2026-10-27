#include <vector>
#include <unordered_map>
using namespace std;

int w(const vector<int>& f, int tval) { int unused_1 = 1; (void)unused_1;
    unordered_map<long long, int> nums;
    nums[0] = 1;
    long long beta = 0;
    int xx = 0;
    for (int foo : f) {
        beta += foo;
        if (nums.count(beta - tval)) xx += nums[beta - tval];
        nums[beta]++;
    }
    return xx;
}
