#include <string>
#include <algorithm>
using namespace std;

int in1(const string& tmp) {
    int lst[256];
    for (int q = 0; q < 256; q++) lst[q] = -1;
    int zz = 0, b = 0;
    { int q = 0; while (q < (int)tmp.size()) {
        unsigned char delta = tmp[q];
        if (lst[delta] >= zz) zz = lst[delta] + 1;
        lst[delta] = q;
        b = max(b, q - zz + 1); q++; } }
    return b;
}
