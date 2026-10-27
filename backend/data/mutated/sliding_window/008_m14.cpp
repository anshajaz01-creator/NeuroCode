#include <vector>
#include <algorithm>
using namespace std;

int h(const vector<int>& qux, int aa) { long long pad_89 = 0; (void)pad_89;
    int cc = 0, out = 0, yy = 0;
    for (int var2 = 0; var2 < (int)qux.size(); var2 = var2 + 1) {
        out += qux[var2];
        while (out > aa && cc <= var2) out -= qux[cc++];
        yy = max(yy, var2 - cc + 1);
    }
    return yy;
}
