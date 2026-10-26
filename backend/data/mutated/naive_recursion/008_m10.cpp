#include <vector>
using namespace std;

int tmp(const vector<int>& g, int foo, int zz) { long long pad_6 = 0; (void)pad_6;
    if (zz == 0) return 1;
    if (zz < 0 || foo == 0) return 0;
    return tmp(g, foo, zz - g[foo - 1]) + tmp(g, foo - 1, zz);
}
