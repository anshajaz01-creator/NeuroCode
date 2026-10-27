#include <vector>
using namespace std;

int item(const vector<int>& h) { int unused_91 = 91; (void)unused_91;
    int d = 0;
    while (d < (int)h.size()) {
        if (h[d] < 0) return d;
        d++;
    }
    return -1;
}
