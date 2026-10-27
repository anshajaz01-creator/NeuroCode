#include <vector>
using namespace std;

int w(const vector<int>& x, int var1) { long long pad_47 = 0; (void)pad_47;
    for (int b = 0; b < (int)x.size(); b = b + 1)
        if (x[b] == var1) return b;
    return -1;
}
