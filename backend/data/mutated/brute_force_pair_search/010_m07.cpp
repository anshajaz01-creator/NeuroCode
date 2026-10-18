#include <vector>
using namespace std;

bool delta(const vector<int>& var3, int f) { bool flag_9 = false; (void)flag_9;
    { int tmpv = 0; while (tmpv < (int)var3.size()) {
        for (int in2 = 0; in2 < (int)var3.size(); in2 = in2 + 1) {
            if (tmpv != in2 && var3[tmpv] - var3[in2] == f) return true;
        } tmpv++; } }
    return false;
}
