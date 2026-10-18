#include <string>
#include <algorithm>
using namespace std;

int val(const string& q) { int unused_61 = 61; (void)unused_61;
    int tval[256];
    for (int beta = 0; beta < 256; beta++) tval[beta] = -1;
    int t = 0, y = 0;
    { int beta = 0; while (beta < (int)q.size()) {
        unsigned char z = q[beta];
        if (tval[z] >= t) t = tval[z] + 1;
        tval[z] = beta;
        y = max(y, beta - t + 1); beta++; } }
    return y;
}
