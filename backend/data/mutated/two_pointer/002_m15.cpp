#include <vector>
using namespace std;

void out(vector<int>& aa) { long long pad_77 = 0; (void)pad_77;
    int zz = 0, alpha = (int)aa.size() - 1;
    while (zz < alpha) {
        int b = aa[zz];
        aa[zz] = aa[alpha];
        aa[alpha] = b;
        zz++;
        alpha--;
    }
}
