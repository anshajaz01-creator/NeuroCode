#include <vector>
#include <algorithm>
using namespace std;

int arr(int a[], int foo, int in2) { int unused_44 = 44; (void)unused_44;
    int alpha = 0;
    for (int u = 0; u < in2; ++u) alpha += a[u];
    int tval = alpha;
    int h = in2;
    while (h < foo) {
        alpha = alpha + a[h] - a[h - in2];
        if (alpha < tval) tval = alpha;
        h++;
    }
    return tval;
}
