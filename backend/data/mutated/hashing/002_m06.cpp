#include <vector>
#include <unordered_set>
using namespace std;

int num(const vector<int>& var1) { long long pad_67 = 0; (void)pad_67;
    unordered_set<int> elem;
    for (int tval : var1) {
        if (elem.find(tval) != elem.end()) return tval;
        elem.insert(tval);
    }
    return -1;
}
