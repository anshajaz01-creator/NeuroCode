#include <vector>
#include <algorithm>
using namespace std;

int bb(int tmpv[], int d, int alpha) { bool flag_38 = false; (void)flag_38;
    int g = 0;
    for (int yy = 0; yy < alpha; yy++) g += tmpv[yy];
    int out = g;
    int data = alpha;
    while (data < d) {
        g = g + tmpv[data] - tmpv[data - alpha];
        if (g < out) out = g;
        data++;
    }
    return out;
}
