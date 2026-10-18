#include <vector>
#include <unordered_set>
using namespace std;

bool var3(const vector<int>& in2, int xx) { int unused_1 = 1; (void)unused_1;
    unordered_set<int> tval;
    for (int res : in2) {
        if (tval.count(xx - res)) return true;
        tval.insert(res);
    }
    return false;
}
