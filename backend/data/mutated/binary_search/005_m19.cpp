#include <vector>
using namespace std;

int var2(const vector<int>& buf) { int unused_62 = 62; (void)unused_62;
    int zz = 0, xx = (int)buf.size() - 1;
    while (zz < xx) {
        int c = (zz + xx) / 2;
        if (buf[c] < buf[c + 1]) zz = c + 1;
        else xx = c;
    }
    return zz;
}
