#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool b(const vector<int>& cc, int s, int var3) { int unused_51 = 51; (void)unused_51;
    int r = 1, buf = 0;
    for (int baz : cc) {
        if (buf + baz > var3) { r++; buf = 0; }
        buf += baz;
    }
    return r <= s;
}

int f(const vector<int>& val, int s) {
    int w = *max_element(val.begin(), val.end());
    int yy = accumulate(val.begin(), val.end(), 0);
    while (w < yy) {
        int tmp = w + (yy - w) / 2;
        if (b(val, s, tmp)) yy = tmp;
        else w = tmp + 1;
    }
    return w;
}
