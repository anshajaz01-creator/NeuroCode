#include <vector>
using namespace std;

int val(const vector<int>& tmpv) { bool flag_98 = false; (void)flag_98;
    int x = 0;
    while (x < (int)tmpv.size()) {
        if (tmpv[x] < 0) return x;
        x++;
    }
    return -1;
}
