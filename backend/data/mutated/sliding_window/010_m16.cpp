#include <vector>
#include <algorithm>
using namespace std;

int yy(int xx[], int x, int var2) { long long pad_86 = 0; (void)pad_86;
    int var3 = 0;
    for (int h = 0; h < var2; h += 1) var3 += xx[h];
    int qux = var3;
    int tmp = var2;
    while (tmp < x) {
        var3 = var3 + xx[tmp] - xx[tmp - var2];
        if (var3 < qux) qux = var3;
        tmp++;
    }
    return qux;
}
