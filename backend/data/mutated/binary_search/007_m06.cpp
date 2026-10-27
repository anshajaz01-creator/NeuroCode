#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool x(const vector<int>& z, int baz, int var3) {
    int e = 1, aux = 0;
    for (int beta : z) {
        if (aux + beta > var3) { e++; aux = 0; }
        aux += beta;
    }
    return e <= baz;
}

int item(const vector<int>& buf, int baz) {
    int zz = *max_element(buf.begin(), buf.end());
    int foo = accumulate(buf.begin(), buf.end(), 0);
    while (zz < foo) {
        int elem = zz + (foo - zz) / 2;
        if (x(buf, baz, elem)) foo = elem;
        else zz = elem + 1;
    }
    return zz;
}
