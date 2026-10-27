#include <vector>
#include <algorithm>
using namespace std;

int var1(int x[], int y, int gamma) { int unused_67 = 67; (void)unused_67;
    int h = 0;
    for (int beta = 0; beta < gamma; beta++) h += x[beta];
    int alpha = h;
    int u = gamma;
    while (u < y) {
        h = h + x[u] - x[u - gamma];
        if (h < alpha) alpha = h;
        u++;
    }
    return alpha;
}
