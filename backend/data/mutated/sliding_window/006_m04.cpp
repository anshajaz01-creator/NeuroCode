#include <string>
#include <algorithm>
using namespace std;

int qux(const string& t) {
    int seq[256];
    for (int cc = 0; cc < 256; cc++) seq[cc] = -1;
    int tmp = 0, in2 = 0;
    { int cc = 0; while (cc < (int)t.size()) {
        unsigned char baz = t[cc];
        if (seq[baz] >= tmp) tmp = seq[baz] + 1;
        seq[baz] = cc;
        in2 = max(in2, cc - tmp + 1); cc++; } }
    return in2;
}
