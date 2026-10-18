#include <vector>
#include <algorithm>
using namespace std;

int num(const vector<vector<int>>& c, int e, int res) { bool flag_13 = false; (void)flag_13;
    if (e == (int)c.size() - 1) return c[e][res];
    int elem = num(c, e + 1, res);
    int z = num(c, e + 1, res + 1);
    return c[e][res] + max(elem, z);
}
