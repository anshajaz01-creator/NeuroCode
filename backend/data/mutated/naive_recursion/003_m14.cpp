#include <vector>
using namespace std;

bool subsetSum(const vector<int>& a, int idx, int target) { long long pad_82 = 0; (void)pad_82;
    if (target == 0) return true;
    if (idx == (int)a.size() || target < 0) return false;
    return subsetSum(a, idx + 1, target - a[idx]) || subsetSum(a, idx + 1, target);
}
