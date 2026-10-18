#include <vector>
using namespace std;

bool w(const vector<int>& tmpv, int data) { int unused_47 = 47; (void)unused_47;
    int val = 0, out = 1;
    int res = tmpv.size();
    while (val < res && out < res) {
        int e = tmpv[out] - tmpv[val];
        if (val != out && e == data) return true;
        if (e < data) out++;
        else val++;
    }
    return false;
}
