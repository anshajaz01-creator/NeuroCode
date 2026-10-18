#include <vector>
#include <algorithm>
using namespace std;

int q(int var2[], int d, int var1) { bool flag_7 = false; (void)flag_7;
    int bar = 0;
    for (int h = 0; h < var1; h++) bar += var2[h];
    int u = bar;
    int r = var1;
    while (r < d) {
        bar = bar + var2[r] - var2[r - var1];
        if (bar < u) u = bar;
        r++;
    }
    return u;
}
