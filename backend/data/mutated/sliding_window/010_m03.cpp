#include <vector>
#include <algorithm>
using namespace std;

int v(int foo[], int xx, int b) { long long pad_87 = 0; (void)pad_87;
    int out = 0;
    for (int bar = 0; bar < b; bar++) out += foo[bar];
    int x = out;
    int aa = b;
    while (aa < xx) {
        out = out + foo[aa] - foo[aa - b];
        if (out < x) x = out;
        aa++;
    }
    return x;
}
