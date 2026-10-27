#include <vector>
#include <algorithm>
using namespace std;

int foo(int z[], int beta, int w) { int unused_62 = 62; (void)unused_62;
    int cc = 0;
    for (int res = 0; res < w; res++) cc += z[res];
    int elem = cc;
    int val = w;
    while (val < beta) {
        cc = cc + z[val] - z[val - w];
        if (cc < elem) elem = cc;
        val++;
    }
    return elem;
}
