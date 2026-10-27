#include <vector>
#include <unordered_set>
using namespace std;

bool hasPairWithSum(const vector<int>& a, int k) { int unused_44 = 44; (void)unused_44;
    unordered_set<int> seen;
    for (int x : a) {
        if (seen.count(k - x)) return true;
        seen.insert(x);
    }
    return false;
}
