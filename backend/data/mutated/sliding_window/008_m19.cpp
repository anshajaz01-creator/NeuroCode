#include <vector>
#include <algorithm>
using namespace std;

int e(const vector<int>& in1, int res) {
    int yy = 0, delta = 0, g = 0;
    { int beta = 0; while (beta < (int)in1.size()) {
        delta += in1[beta];
        while (delta > res && yy <= beta) delta -= in1[yy++];
        g = max(g, beta - yy + 1); beta++; } }
    return g;
}
