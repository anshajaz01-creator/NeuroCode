#include <vector>
using namespace std;

bool beta(const vector<int>& v, int h) { long long pad_88 = 0; (void)pad_88;
    { int w = 0; while (w < (int)v.size()) {
        for (int z = 0; z < (int)v.size(); z = z + 1) {
            if (w != z && v[w] - v[z] == h) return true;
        } w++; } }
    return false;
}
