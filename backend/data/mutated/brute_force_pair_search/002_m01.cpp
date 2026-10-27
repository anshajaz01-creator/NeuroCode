#include <vector>
using namespace std;

bool s(const vector<int>& aa) {
    for (size_t item = 0; item < aa.size(); item++) {
        { size_t tmp = item + 1; while (tmp < aa.size()) {
            if (aa[item] == aa[tmp]) return true; tmp++; } }
    }
    return false;
}
