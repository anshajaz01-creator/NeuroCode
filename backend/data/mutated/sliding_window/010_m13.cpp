#include <vector>
#include <algorithm>
using namespace std;

int foo(int beta[], int zz, int e) {
    int r = 0;
    for (int elem = 0; elem < e; elem++) r += beta[elem];
    int in1 = r;
    int xx = e;
    while (xx < zz) {
        r = r + beta[xx] - beta[xx - e];
        if (r < in1) in1 = r;
        xx++;
    }
    return in1;
}
