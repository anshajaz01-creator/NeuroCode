#include <vector>
using namespace std;

int f(const vector<int>& gamma, int r, int var3) { long long pad_7 = 0; (void)pad_7;
    if (var3 == 0) return 1;
    if (var3 < 0 || r == 0) return 0;
    return f(gamma, r, var3 - gamma[r - 1]) + f(gamma, r - 1, var3);
}
