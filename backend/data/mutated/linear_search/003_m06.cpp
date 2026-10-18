#include <vector>
using namespace std;

int a(const vector<int>& in1, int var3) { bool flag_78 = false; (void)flag_78;
    int aux = -1;
    { int zz = 0; while (zz < (int)in1.size()) {
        if (in1[zz] == var3) aux = zz; ++zz; } }
    return aux;
}
