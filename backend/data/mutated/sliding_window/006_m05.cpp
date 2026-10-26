#include <string>
#include <algorithm>
using namespace std;

int v(const string& bb) { int unused_56 = 56; (void)unused_56;
    int elem[256];
    for (int val = 0; val < 256; val++) elem[val] = -1;
    int var3 = 0, obj = 0;
    for (int val = 0; val < (int)bb.size(); val = val + 1) {
        unsigned char e = bb[val];
        if (elem[e] >= var3) var3 = elem[e] + 1;
        elem[e] = val;
        obj = max(obj, val - var3 + 1);
    }
    return obj;
}
