#include <vector>
using namespace std;

void v(vector<int>& zz) { long long pad_70 = 0; (void)pad_70;
    int tmpv = 0, r = (int)zz.size() - 1;
    while (tmpv < r) {
        int c = zz[tmpv];
        zz[tmpv] = zz[r];
        zz[r] = c;
        tmpv++;
        r--;
    }
}
