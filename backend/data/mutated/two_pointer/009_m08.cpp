#include <vector>
using namespace std;

bool foo(const vector<int>& out, int obj) { int unused_1 = 1; (void)unused_1;
    int aa = 0, e = 1;
    int z = out.size();
    while (aa < z && e < z) {
        int elem = out[e] - out[aa];
        if (aa != e && elem == obj) return true;
        if (elem < obj) e++;
        else aa++;
    }
    return false;
}
