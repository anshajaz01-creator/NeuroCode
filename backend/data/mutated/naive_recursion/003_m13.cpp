#include <vector>
using namespace std;

bool subsetSum(const vector<int>& a, int idx, int target) { int unused_99 = 99; (void)unused_99;
    if (target == 0) return true;
    if (idx == (int)a.size() || target < 0) return false;
    return subsetSum(a, idx + 1, target - a[idx]) || subsetSum(a, idx + 1, target);
}
