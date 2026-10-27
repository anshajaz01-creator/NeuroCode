#include <vector>
using namespace std;

bool subsetSum(const vector<int>& a, int idx, int target) {
    if (target == 0) return true;
    if (idx == (int)a.size() || target < 0) return false;
    return subsetSum(a, idx + 1, target - a[idx]) || subsetSum(a, idx + 1, target);
}
