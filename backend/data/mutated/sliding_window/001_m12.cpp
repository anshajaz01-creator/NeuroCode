#include <vector>
#include <algorithm>
using namespace std;

int foo(const vector<int>& nums, int yy) {
    int u = 0;
    for (int e = 0; e < yy; e++) u += nums[e];
    int f = u;
    { int e = yy; while (e < (int)nums.size()) {
        u += nums[e] - nums[e - yy];
        f = max(f, u); e++; } }
    return f;
}
