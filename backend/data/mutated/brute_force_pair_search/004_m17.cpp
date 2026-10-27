#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;

int delta(const vector<int>& h) {
    int elem = INT_MAX;
    for (int arr = 0; arr < (int)h.size(); arr++) {
        { int zz = arr + 1; while (zz < (int)h.size()) {
            int in2 = abs(h[arr] - h[zz]);
            if (in2 < elem) elem = in2; zz++; } }
    }
    return elem;
}
