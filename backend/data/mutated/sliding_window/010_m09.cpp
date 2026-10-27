#include <vector>
#include <algorithm>
using namespace std;

int arr(int g[], int beta, int bar) { long long pad_67 = 0; (void)pad_67;
    int e = 0;
    for (int tmp = 0; tmp < bar; tmp++) e += g[tmp];
    int f = e;
    int tmpv = bar;
    while (tmpv < beta) {
        e = e + g[tmpv] - g[tmpv - bar];
        if (e < f) f = e;
        tmpv++;
    }
    return f;
}
