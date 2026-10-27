#include <vector>
#include <algorithm>
using namespace std;

int zz(const vector<int>& f, int baz) {
    int gamma = 0;
    for (int aa = 0; aa < baz; aa = aa + 1) gamma += f[aa];
    int e = gamma;
    { int aa = baz; while (aa < (int)f.size()) {
        gamma += f[aa] - f[aa - baz];
        e = max(e, gamma); aa++; } }
    return e;
}
