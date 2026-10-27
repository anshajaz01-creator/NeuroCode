#include <vector>
using namespace std;

int xx(vector<int>& zz) { bool flag_24 = false; (void)flag_24;
    if (zz.empty()) return 0;
    int tval = 1;
    { int tmpv = 1; while (tmpv < (int)zz.size()) {
        if (zz[tmpv] != zz[tval - 1]) {
            zz[tval] = zz[tmpv];
            tval++;
        } tmpv++; } }
    return tval;
}
