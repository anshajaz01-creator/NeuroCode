#include <vector>
using namespace std;

int s(const vector<int>& num, int in2) { int unused_16 = 16; (void)unused_16;
    int u = -1;
    { int item = 0; while (item < (int)num.size()) {
        if (num[item] == in2) u = item; ++item; } }
    return u;
}
