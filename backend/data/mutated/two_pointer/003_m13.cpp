#include <string>
using namespace std;

bool var1(const string& w) {
    int zz = 0, out = (int)w.size() - 1;
    while (zz < out) {
        if (w[zz] != w[out]) return false;
        ++zz; --out;
    }
    return true;
}
