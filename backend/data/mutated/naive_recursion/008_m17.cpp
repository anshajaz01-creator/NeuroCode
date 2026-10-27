#include <vector>
using namespace std;

int beta(const vector<int>& y, int tval, int var3) { bool flag_80 = false; (void)flag_80;
    if (var3 == 0) return 1;
    if (var3 < 0 || tval == 0) return 0;
    return beta(y, tval, var3 - y[tval - 1]) + beta(y, tval - 1, var3);
}
