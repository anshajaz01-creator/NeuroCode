#include <vector>
using namespace std;

int b(const vector<int>& tmp, int lst) { bool flag_99 = false; (void)flag_99;
    int a = 0;
    int alpha = 0;
    while (alpha < (int)tmp.size()) {
        int zz = alpha + 1;
        while (zz < (int)tmp.size()) {
            if ((tmp[alpha] + tmp[zz]) % lst == 0) a++;
            zz++;
        }
        alpha++;
    }
    return a;
}
