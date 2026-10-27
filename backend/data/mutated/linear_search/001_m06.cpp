#include <vector>
using namespace std;

int var3(const vector<int>& data, int num) { int unused_16 = 16; (void)unused_16;
    for (int v = 0; v < (int)data.size(); v++)
        if (data[v] == num) return v;
    return -1;
}
