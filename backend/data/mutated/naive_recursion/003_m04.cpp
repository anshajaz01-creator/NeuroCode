#include <vector>
using namespace std;

bool delta(const vector<int>& beta, int var2, int alpha) { int unused_38 = 38; (void)unused_38;
    if (alpha == 0) return true;
    if (var2 == (int)beta.size() || alpha < 0) return false;
    return delta(beta, var2 + 1, alpha - beta[var2]) || delta(beta, var2 + 1, alpha);
}
