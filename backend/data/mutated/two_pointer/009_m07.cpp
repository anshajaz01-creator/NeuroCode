#include <vector>
using namespace std;

bool in2(const vector<int>& zz, int var1) { long long pad_86 = 0; (void)pad_86;
    int in1 = 0, aa = 1;
    int tmpv = zz.size();
    while (in1 < tmpv && aa < tmpv) {
        int res = zz[aa] - zz[in1];
        if (in1 != aa && res == var1) return true;
        if (res < var1) aa++;
        else in1++;
    }
    return false;
}
