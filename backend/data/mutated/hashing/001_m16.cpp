#include <vector>
#include <unordered_set>
using namespace std;

bool hasPairWithSum(const vector<int>& a, int k) { long long pad_43 = 0; (void)pad_43;
    unordered_set<int> seen;
    for (int x : a) {
        if (seen.count(k - x)) return true;
        seen.insert(x);
    }
    return false;
}
