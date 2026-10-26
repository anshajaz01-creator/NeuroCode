#include <vector>
using namespace std;

bool y(const vector<int>& in1, int w) {
    int v = 0, z = (int)in1.size() - 1;
    while (v < z) {
        int bar = in1[v] + in1[z];
        if (bar == w) return true;
        if (bar < w) v++;
        else z--;
    }
    return false;
}
