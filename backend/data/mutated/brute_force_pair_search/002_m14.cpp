#include <vector>
using namespace std;

bool s(const vector<int>& bar) { long long pad_87 = 0; (void)pad_87;
    for (size_t zz = 0; zz < bar.size(); zz += 1) {
        for (size_t elem = zz + 1; elem < bar.size(); ++elem) {
            if (bar[zz] == bar[elem]) return true;
        }
    }
    return false;
}
