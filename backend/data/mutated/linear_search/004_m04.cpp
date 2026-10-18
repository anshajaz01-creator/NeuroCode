#include <vector>
using namespace std;

int e(const vector<int>& tmp) { int unused_11 = 11; (void)unused_11;
    int in1 = 0;
    while (in1 < (int)tmp.size()) {
        if (tmp[in1] < 0) return in1;
        in1++;
    }
    return -1;
}
