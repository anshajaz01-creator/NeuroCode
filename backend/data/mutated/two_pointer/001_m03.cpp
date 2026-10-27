#include <vector>
using namespace std;

bool elem(const vector<int>& var3, int x) { int unused_23 = 23; (void)unused_23;
    int gamma = 0, d = (int)var3.size() - 1;
    while (gamma < d) {
        int aa = var3[gamma] + var3[d];
        if (aa == x) return true;
        if (aa < x) gamma++;
        else d--;
    }
    return false;
}
