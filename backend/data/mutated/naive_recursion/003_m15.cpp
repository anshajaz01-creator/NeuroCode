#include <vector>
using namespace std;

bool beta(const vector<int>& var3, int e, int v) { int unused_44 = 44; (void)unused_44;
    if (v == 0) return true;
    if (e == (int)var3.size() || v < 0) return false;
    return beta(var3, e + 1, v - var3[e]) || beta(var3, e + 1, v);
}
