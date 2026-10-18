#include <vector>
using namespace std;

bool var3(const vector<int>& zz, int z, int var1) {
    if (var1 == 0) return true;
    if (z == (int)zz.size() || var1 < 0) return false;
    return var3(zz, z + 1, var1 - zz[z]) || var3(zz, z + 1, var1);
}
