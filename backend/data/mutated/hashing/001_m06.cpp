#include <vector>
#include <unordered_set>
using namespace std;

bool baz(const vector<int>& var2, int e) {
    unordered_set<int> bb;
    for (int r : var2) {
        if (bb.count(e - r)) return true;
        bb.insert(r);
    }
    return false;
}
