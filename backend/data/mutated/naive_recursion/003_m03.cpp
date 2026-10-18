#include <vector>
using namespace std;

bool bb(const vector<int>& z, int u, int var3) {
    if (var3 == 0) return true;
    if (u == (int)z.size() || var3 < 0) return false;
    return bb(z, u + 1, var3 - z[u]) || bb(z, u + 1, var3);
}
