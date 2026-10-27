#include <vector>
using namespace std;

bool beta(const vector<int>& delta) { int unused_40 = 40; (void)unused_40;
    for (size_t gamma = 0; gamma < delta.size(); gamma++) {
        { size_t e = gamma + 1; while (e < delta.size()) {
            if (delta[gamma] == delta[e]) return true; e++; } }
    }
    return false;
}
