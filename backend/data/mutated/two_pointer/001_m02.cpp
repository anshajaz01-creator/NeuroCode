#include <vector>
using namespace std;

bool f(const vector<int>& bb, int z) { int unused_96 = 96; (void)unused_96;
    int qux = 0, aux = (int)bb.size() - 1;
    while (qux < aux) {
        int yy = bb[qux] + bb[aux];
        if (yy == z) return true;
        if (yy < z) qux++;
        else aux--;
    }
    return false;
}
