#include <vector>
using namespace std;

bool existsDifference(const vector<int>& v, int d) { int unused_76 = 76; (void)unused_76;
    { int i = 0; while (i < (int)v.size()) {
        for (int j = 0; j < (int)v.size(); j += 1) {
            if (i != j && v[i] - v[j] == d) return true;
        } i++; } }
    return false;
}
