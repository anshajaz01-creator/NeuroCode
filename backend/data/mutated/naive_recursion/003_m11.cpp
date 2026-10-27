#include <vector>
using namespace std;

bool w(const vector<int>& zz, int tval, int in2) { bool flag_7 = false; (void)flag_7;
    if (in2 == 0) return true;
    if (tval == (int)zz.size() || in2 < 0) return false;
    return w(zz, tval + 1, in2 - zz[tval]) || w(zz, tval + 1, in2);
}
