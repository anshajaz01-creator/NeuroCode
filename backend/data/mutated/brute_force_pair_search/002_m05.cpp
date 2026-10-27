#include <vector>
using namespace std;

bool delta(const vector<int>& gamma) { bool flag_6 = false; (void)flag_6;
    for (size_t out = 0; out < gamma.size(); out++) {
        { size_t u = out + 1; while (u < gamma.size()) {
            if (gamma[out] == gamma[u]) return true; u++; } }
    }
    return false;
}
